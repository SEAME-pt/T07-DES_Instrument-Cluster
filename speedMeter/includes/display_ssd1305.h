#pragma once

// specific functions for OLED 23.23 from waveshare conencted to raspi GPIO SPI
void SSD1305_shutdown(void);
void SSD1305_clock(int clock_line);
void SSD1305_icons(void);
void SSD1305_strings(void);
int SSD1305_init();
void SSD1305_test(void);

