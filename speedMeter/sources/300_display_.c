#include "../includes/speedMeter.h"

void display_clear(void)
{
	SSD1305_clear();
}
void display_expose(void)
{
	SSD1305_display();
}

void display_shutdown(void)
{
	printf("> Display Clear\n");
	display_clear();
	display_expose();
	printf("> DEV Module Exit\n");
	DEV_ModuleExit();
}

void display_clock(int clock_line)
{
	SSD1305_clock(clock_line);
}

void display_bitmap(int x, int y, const unsigned char *bmp, int charWidth, int charHeight)
{
	SSD1305_bitmap(x, y, bmp, charWidth, charHeight);
}

void display_icons(void)
{

	display_bitmap(0, 2, Signal816, 16, 8);
	display_bitmap(24, 2, Bluetooth88, 8, 8);
	display_bitmap(40, 2, Msg816, 16, 8);
	display_bitmap(64, 2, GPRS88, 8, 8);
	display_bitmap(90, 2, Alarm88, 8, 8);
	display_bitmap(112, 2, Bat816, 16, 8);
	display_expose();
}


void display_string(int x, int y, char *string, int charSize, int color)
{
	SSD1305_string(x, y, string, charSize, color);
}

void display_strings(void)
{
	display_string(0, 52, "MUSIC", 12, 0);
	display_string(52, 52, "MENU", 12, 0);
	display_string(98, 52, "PHONE", 12, 0);

}

int display_init()
{
	return (SSD1305_init());
}

void display_test(void)
{
	SSD1305_test();
}
