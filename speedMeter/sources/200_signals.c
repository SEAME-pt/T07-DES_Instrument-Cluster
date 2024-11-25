#include "../includes/speedMeter.h"

// Signal handler for clean exit
void handle_signal(int signal)
{
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
