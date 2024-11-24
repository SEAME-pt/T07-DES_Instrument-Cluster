
#pragma once

#ifdef USE_BCM2835_LIB
    #include <bcm2835.h>
#elif USE_WIRINGPI_LIB
    #include <wiringPi.h>
    #include <wiringPiSPI.h>
	#include <wiringPiI2C.h>
#elif USE_DEV_LIB
    #include <lgpio.h>
    #define LFLAGS 0
    #define NUM_MAXBUF  4
#endif


#define SPEED_SENSOR_PIN	17
#define SPEED_STATUS 27
