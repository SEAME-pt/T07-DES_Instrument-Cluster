// File: gpio_pulse_counter_threaded.c
#include "../includes/speedMeter.h"



// GPIO chip and line
struct gpiod_chip *chip = NULL;
struct gpiod_line *line = NULL;

// Global variables
volatile int gpulses = 0;			// Total pulse count
volatile int gpulses_per_period = 0;// Pulse count for the last period
pthread_mutex_t mutex;				// Mutex for synchronization
int running = 1;


void display_text(const char *text)
{
	SSD1305_string(76, 8, text, 8, 1);
	SSD1305_display();
}

int main() {
	pthread_t pulse_thread;

	// Set up signal handling for cleanup
	signal(SIGINT, handle_signal);

	if (SSD1305_init() < 0) exit (-1);
		SSD1305_test();

	// Initialize global variables
	gpulses = 0;
	gpulses_per_period = 0;
	running = 1;

	display_text("km/h");
	sleep(2);

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

//				time(&now);

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
			display_speed(ppp);
			speed_update = 0;
		}
		usleep(100000);  // 100ms

//		sleep(PERIOD);
	}

	// Wait for the pulse counting thread to finish
	pthread_join(pulse_thread, NULL);

	// Cleanup
	gpiod_line_release(line);
	gpiod_chip_close(chip);
	pthread_mutex_destroy(&mutex);

	return 0;
}
