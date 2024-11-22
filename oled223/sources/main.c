// File: gpio_pulse_counter_threaded.c
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "test.h"

#define GPIO_CHIP "/dev/gpiochip0" // GPIO chip device
#define GPIO_LINE 17              // GPIO line (pin number)
#define PERIOD 3                  // Period to update counts in seconds
#define PPR 4
#define PERIMETER 215

// Global variables
volatile int gpulses = 0;              // Total pulse count
volatile int gpulses_per_period = 0;   // Pulse count for the last period
pthread_mutex_t mutex;                 // Mutex for synchronization
int running = 1;                       // Control flag for the thread

// GPIO chip and line
struct gpiod_chip *chip = NULL;
struct gpiod_line *line = NULL;


#define INTERVAL_SEC 10
#define CLOCK_LINE 1 //  line 0 or line 1 for 16 pixel chars


void SSD1305_shutdown(void)
{
    printf("> Display Clear\n");
    SSD1305_clear();
    SSD1305_display();
    printf("> DEV Module Exit\n");
    DEV_ModuleExit();
}

void SSD1305_clock(int clock_line)
{
    char value[10]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    time_t now;
    struct tm *timenow;
    int line = clock_line * 16; 
    time(&now);
    timenow = localtime(&now);

    SSD1305_char1616(0, line, value[timenow->tm_hour/10]);
    SSD1305_char1616(16, line, value[timenow->tm_hour%10]);
    SSD1305_char1616(32, line, ':');
    SSD1305_char1616(48, line, value[timenow->tm_min/10]);
    SSD1305_char1616(64, line, value[timenow->tm_min%10]);
    SSD1305_char1616(80, line, ':');
    SSD1305_char1616(96, line, value[timenow->tm_sec/10]);
    SSD1305_char1616(112, line, value[timenow->tm_sec%10]);
    SSD1305_display();
}

void SSD1305_icons(void)
{
    SSD1305_bitmap(0, 2, Signal816, 16, 8);
    SSD1305_bitmap(24, 2, Bluetooth88, 8, 8);
    SSD1305_bitmap(40, 2, Msg816, 16, 8);
    SSD1305_bitmap(64, 2, GPRS88, 8, 8);
    SSD1305_bitmap(90, 2, Alarm88, 8, 8);
    SSD1305_bitmap(112, 2, Bat816, 16, 8);
    SSD1305_display();
}

void SSD1305_strings(void)
{
    SSD1305_string(0, 52, "MUSIC", 12, 0);
    SSD1305_string(52, 52, "MENU", 12, 0);
    SSD1305_string(98, 52, "PHONE", 12, 0);

}

int SSD1305_init()
{
   
    if(DEV_ModuleInit() != 0) {
	    return -1;
    }
    SSD1305_begin();
    return (0);
}

void SSD1305_test(void)
{
    int j = 2;
    while(j--)
    {
        SSD1305_bitmap(0, 0, seame, 128,32);
        SSD1305_display();
        DEV_Delay_ms(500);
        SSD1305_clear();
        // SSD1305_bitmap(0, 1, seame, 128,32);
        SSD1305_display();
        DEV_Delay_ms(500);
        SSD1305_clear();
    }
} 

void SD1305_speedmeter(int ppp)
{
    char value[10]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int line = 0; 

    float kmph  = ((float)ppp / PPR ) * PERIMETER;
    printf("ppp : %d\n", ppp);
    printf("km/h : %f\n", kmph);
    int hundreds = ((int)kmph / 100) % 10; // Extract hundreds place
    int tens = ((int)kmph / 10) % 10;      // Extract tens place
    int units = (int)kmph % 10;  
    SSD1305_char1616(32, line, value[hundreds]);
    SSD1305_char1616(48, line, value[tens]);
    SSD1305_char1616(64, line, value[units]);
    SSD1305_display();
}


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
    SSD1305_shutdown();

    printf("\nExiting... Cleanup done.\n");
    exit(0);
}

int main() {
    pthread_t pulse_thread;

    // Set up signal handling for cleanup
    signal(SIGINT, handle_signal);

    if (SSD1305_init() < 0) exit (-1);
    SSD1305_test();    


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
    int speed_update = 0;
    int ppp = 0;
    //SSD1305_icons();
    while (running) {

//                time(&now);

        //SSD1305_strings();
        SSD1305_clock(CLOCK_LINE);
        speed_update++;
        //printf("spedd update : %d\n", speed_update%10);
        if (!(speed_update%10))
        {
            printf("Speed update!\n");
            pthread_mutex_lock(&mutex);
            ppp = gpulses - local_pulses;
            printf("Last period count: %d | Total pulses: %d\n", gpulses_per_period, ppp);
            local_pulses = gpulses;
            pthread_mutex_unlock(&mutex);
            SD1305_speedmeter(ppp);
            speed_update = 0;
        }
        usleep(100000);  // 100ms

//        sleep(PERIOD);
    }

    // Wait for the pulse counting thread to finish
    pthread_join(pulse_thread, NULL);

    // Cleanup
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    pthread_mutex_destroy(&mutex);

    return 0;
}
