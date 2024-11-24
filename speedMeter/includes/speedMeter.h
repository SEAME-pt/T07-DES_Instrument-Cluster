#ifndef SPEEDMETER_H
#define SPEEDMETER_H

# include "display.h"
# include "display_ssd1305.h"
# include "DEV_Config.h"
# include "Debug.h"
# include "ssd1305.h"

# include <gpiod.h>
# include <stdio.h>
# include <stdlib.h> // malloc() free()
# include <pthread.h>
# include <signal.h>     //signal()
# include <unistd.h>
# include <time.h>
# include <string.h>
# include <math.h>

// Global settings
#define GPIO_CHIP "/dev/gpiochip0"	// GPIO chip device

// Spedd meter settings
#define GPIO_LINE 17				// ENCODER INPUT GPIO line @raspi 4B  (I/O number)

// Speed encoder settings
#define PPR 4						// Pulses per revolution
#define PERIMETER 0.215				// Wheel perimeter in meters

// Speed calculation settings
#define PERIOD 1					// Period to update counts in seconds
#define INTERVAL_SEC 10				// Interval to update speed in seconds
#define CLOCK_LINE 1				// Line 0 or line 1 for 16 pixel chars

// GPIO chip and line
extern struct gpiod_chip *chip; //= NULL;
extern struct gpiod_line *line; //= NULL;

// Global variables
extern volatile int gpulses; //= 0;			// Total pulse count
extern volatile int gpulses_per_period; // = 0;// Pulse count for the last period
extern pthread_mutex_t mutex;				// Mutex for synchronization
extern int running; // = 1;					// Control flag for the thread

void SSD1305_shutdown(void);
void SSD1305_clock(int clock_line);
void SSD1305_icons(void);
void SSD1305_strings(void);
int SSD1305_init();
void SSD1305_test(void);

void *pulse_count(void *arg);
void handle_signal(int signal);
void display_speed(int ppp);

#endif