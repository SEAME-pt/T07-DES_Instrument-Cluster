// File: gpio_pulse_counter_threaded.c
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define GPIO_CHIP "/dev/gpiochip0" // GPIO chip device
#define GPIO_LINE 17              // GPIO line (pin number)
#define PERIOD 3                  // Period to update counts in seconds

// Global variables
volatile int gpulses = 0;              // Total pulse count
volatile int gpulses_per_period = 0;   // Pulse count for the last period
pthread_mutex_t mutex;                 // Mutex for synchronization
int running = 1;                       // Control flag for the thread

// GPIO chip and line
struct gpiod_chip *chip = NULL;
struct gpiod_line *line = NULL;

// Function to count pulses in a thread
void *pulse_count(void *arg) {
    struct gpiod_line_event event;
    struct timespec timeout = {PERIOD, 0}; // Timeout for event wait
    int local_count = 0;

    while (running) {
        int ret = gpiod_line_event_wait(line, &timeout);

        if (ret > 0) { // Event occurred
            if (gpiod_line_event_read(line, &event) == 0 &&
                event.event_type == GPIOD_LINE_EVENT_RISING_EDGE) {
                local_count++;
            }
        } else if (ret < 0) { // Error occurred
            perror("Error waiting for GPIO event");
            running = 0;
            break;
        }

        // Update global variables periodically
        pthread_mutex_lock(&mutex);
        gpulses_per_period = local_count; // Update pulses for the last period
        gpulses += local_count;           // Add to total pulse count
        pthread_mutex_unlock(&mutex);

        local_count = 0; // Reset local count for the next period
    }

    return NULL;
}

// Signal handler for clean exit
void handle_signal(int signal) {
    running = 0;
    if (line) {
        gpiod_line_release(line);
    }
    if (chip) {
        gpiod_chip_close(chip);
    }
    pthread_mutex_destroy(&mutex);
    printf("\nExiting... Cleanup done.\n");
    exit(0);
}

int main() {
    pthread_t pulse_thread;

    // Set up signal handling for cleanup
    signal(SIGINT, handle_signal);

    // Initialize mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        fprintf(stderr, "Failed to initialize mutex.\n");
        return EXIT_FAILURE;
    }

    // Open GPIO chip
    chip = gpiod_chip_open(GPIO_CHIP);
    if (!chip) {
        perror("Failed to open GPIO chip");
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    // Get GPIO line 17
    line = gpiod_chip_get_line(chip, GPIO_LINE);
    if (!line) {
        perror("Failed to get GPIO line");
        gpiod_chip_close(chip);
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    // Configure GPIO line as input with edge detection
    if (gpiod_line_request_both_edges_events(line, "gpio_pulse_counter") < 0) {
        perror("Failed to configure GPIO line for edge events");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    // Create the pulse counting thread
    if (pthread_create(&pulse_thread, NULL, pulse_count, NULL) != 0) {
        fprintf(stderr, "Failed to create pulse counting thread.\n");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    printf("Monitoring pulses on GPIO %d. Press Ctrl+C to stop.\n", GPIO_LINE);

    // Main loop to print counts
    int local_pulses = gpulses;
    while (running) {
        pthread_mutex_lock(&mutex);
        printf("Last period count: %d | Total pulses: %d\n", gpulses_per_period, gpulses - local_pulses);
        local_pulses = gpulses;
        pthread_mutex_unlock(&mutex);
        
        sleep(PERIOD);
    }

    // Wait for the pulse counting thread to finish
    pthread_join(pulse_thread, NULL);

    // Cleanup
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    pthread_mutex_destroy(&mutex);

    return 0;
}
