#pragma once

void display_clear(void);
void display_expose(void);
void display_shutdown(void);
void display_clock(int clock_line);
void display_bitmap(int x, int y, const unsigned char *bmp, int charWidth, int charHeight);
void display_icons(void);
void display_string(int x, int y, char *string, int charSize, int color);
void display_strings(void);
int display_init();
void display_test(void);
