#include "../includes/speedMeter.h"

// Function to count pulses in a thread
void *pulse_count(void *arg)
{
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
		gpulses += local_count;		   // Add to total pulse count
		pthread_mutex_unlock(&mutex);

		local_count = 0; // Reset local count for the next period
	}

	return NULL;
}
