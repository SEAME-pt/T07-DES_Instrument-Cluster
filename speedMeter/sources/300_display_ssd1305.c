#include "../includes/speedMeter.h"

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
	int display_line = clock_line * 16; // 16 pixel line for 16 pixel chars
	time(&now);
	timenow = localtime(&now);

	SSD1305_char1616(0, display_line, value[timenow->tm_hour/10]);
	SSD1305_char1616(16, display_line, value[timenow->tm_hour%10]);
	SSD1305_char1616(32, display_line, ':');
	SSD1305_char1616(48, display_line, value[timenow->tm_min/10]);
	SSD1305_char1616(64, display_line, value[timenow->tm_min%10]);
	SSD1305_char1616(80, display_line, ':');
	SSD1305_char1616(96, display_line, value[timenow->tm_sec/10]);
	SSD1305_char1616(112, display_line, value[timenow->tm_sec%10]);
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
