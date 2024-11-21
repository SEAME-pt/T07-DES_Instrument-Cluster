#include "test.h"

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_ModuleExit();

    exit(0);
}

int main(int argc, char *argv[])
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    char value[10]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    time_t now;
    struct tm *timenow;

    if(DEV_ModuleInit() != 0) {
		return -1;
	}
    SSD1305_begin();
    SSD1305_bitmap(7, 0, waveshare_ch,112,32);
    SSD1305_display();
    DEV_Delay_ms(1000);
    SSD1305_clear();
    SSD1305_bitmap(0, 8, waveshare_en,128,32);
    SSD1305_display();
    DEV_Delay_ms(5000);
    SSD1305_clear();
    while(1)
    {
        time(&now);
        timenow = localtime(&now);

        SSD1305_bitmap(0, 2, Signal816, 16, 8);
        SSD1305_bitmap(24, 2, Bluetooth88, 8, 8);
        SSD1305_bitmap(40, 2, Msg816, 16, 8);
        SSD1305_bitmap(64, 2, GPRS88, 8, 8);
        SSD1305_bitmap(90, 2, Alarm88, 8, 8);
        SSD1305_bitmap(112, 2, Bat816, 16, 8);

        SSD1305_string(0, 52, "MUSIC", 12, 0);
        SSD1305_string(52, 52, "MENU", 12, 0);
        SSD1305_string(98, 52, "PHONE", 12, 0);

        SSD1305_char1616(0, 16, value[timenow->tm_hour/10]);
        SSD1305_char1616(16, 16, value[timenow->tm_hour%10]);
        SSD1305_char1616(32, 16, ':');
        SSD1305_char1616(48, 16, value[timenow->tm_min/10]);
        SSD1305_char1616(64, 16, value[timenow->tm_min%10]);
        SSD1305_char1616(80, 16, ':');
        SSD1305_char1616(96, 16, value[timenow->tm_sec/10]);
        SSD1305_char1616(112, 16, value[timenow->tm_sec%10]);

        SSD1305_display();
    }
    return 0;

}
