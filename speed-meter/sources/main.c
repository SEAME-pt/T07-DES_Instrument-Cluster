#include "test.h"

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    SSD1305_clear();
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

    SSD1305_bitmap(0, 8, seame, 128,32);
    SSD1305_display();
    DEV_Delay_ms(5000);
    SSD1305_clear();

   // speed();
    
        // Obter o chip GPIO (geralmente /dev/gpiochip0 para a maioria dos sistemas)
    struct gpiod_chip *chip = gpiod_chip_open_by_name("gpiochip0");

    if (!chip) {
        printf("Fail to open chip GPIO");
        return -1;
    }

    // Obter o pino GPIO 18 (correspondente ao GPIO 18 no chip)
    struct gpiod_line *line_in = gpiod_chip_get_line(chip, SPEED_SENSOR_PIN);
    struct gpiod_line *line_out = gpiod_chip_get_line(chip, SPEED_STATUS);

    if (!line_out) {
        printf("Fail to get pin GPIO %d\n", SPEED_SENSOR_PIN);
        gpiod_chip_close(chip);
        return -1;
    }

    // Configurar o pino como entrada com resistor pull-up
    int ret = gpiod_line_request_input(line_in, "speed_sensor");
    if (ret < 0) {
        printf("Fail to config pin as enter: %d\n", ret);
        gpiod_chip_close(chip);
        return -1;
    }

    // Configuração do pull-up (alteração feita aqui)
    ret = gpiod_line_set_flags(line_in, GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP);
    if (ret < 0) {
        printf("Erro to config the pull-up: %d\n", ret);
        gpiod_chip_close(chip);
        return -1;
    }

    // Configurar a linha como saída
    int ret_out = gpiod_line_request_output(line_out, "gpio_led", 0); // 0 significa valor inicial desligado
    if (ret_out < 0) {
        perror("Erro ao configurar a linha GPIO como saída");
        gpiod_chip_close(chip);
        return -1;
    }

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

    //while (1) {
        // Ler o estado do pino (HIGH ou LOW)
        int value = gpiod_line_get_value(line_in);

        if (value < 0) {
            printf("Erro to read pin value\n");
            break;
        }

	printf("value: %d\n", value);
        // Verifique se o pino está em LOW (pressionado)
        if (value == 0) {
            printf("Pressed\n");
	    gpiod_line_set_value(line_out, 0); 
        } else {
	    gpiod_line_set_value(line_out, 1); 
            printf("Not Pressed\n");
        }

        usleep(100000);  // 100ms
    }

    gpiod_chip_close(chip);

    //}
    return 0;

}
