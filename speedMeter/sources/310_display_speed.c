#include "../includes/speedMeter.h"

// Display speed on the display
void display_speed(int ppp)
{
	char value[10]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int display_line = 0;

	float kmph  = ((3.6f * (float)ppp * PERIMETER) / PPR);// * PERIOD) * 3.6;
	
	int tens_of_thousands = ((int)kmph / 10000) % 10;	// Extract tens of thousands place
	int thownsand = ((int)kmph / 1000) % 10;	// Extract thousands place
	int hundreds = ((int)kmph / 100) % 10;	// Extract hundreds place
	int tens = ((int)kmph / 10) % 10;		// Extract tens place
	int units = (int)kmph % 10;

	if (ppp) {
		printf("ppp : %d\n", ppp);
		printf("km/h : %f\n", kmph);
		printf("tens_of_thousands : %d\n", tens_of_thousands);
		printf("thousands : %d\n", thownsand);
		printf("hundreds : %d\n", hundreds);
		printf("tens : %d\n", tens);
		printf("units : %d\n", units);
	}
	SSD1305_char1616(40, display_line, value[hundreds]);
	SSD1305_char1616(56, display_line, value[tens]);
	SSD1305_char1616(72, display_line, value[units]);
	SSD1305_display();
}