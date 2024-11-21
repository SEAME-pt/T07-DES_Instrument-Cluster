#include "test.h"
#include <time.h>

#define INTERVAL_SEC 10

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_ModuleExit();
    SSD1305_clear();

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
    struct gpiod_line_event event;
    
    if (!line_in) {
        printf("Fail to get pin GPIO %d\n", SPEED_SENSOR_PIN);
        gpiod_chip_close(chip);
        return -1;
    }

    if (!line_out) {
        printf("Fail to get pin GPIO %d\n", SPEED_SENSOR_PIN);
        gpiod_chip_close(chip);
        return -1;
    }

    // Request line as input with edge detection
    if (gpiod_line_request_both_edges_events(line_in, "speed_sensor") < 0) {
        perror("Failed to configure GPIO line for events");
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
    time_t start_time = time(NULL); 
    int impulse_count = 0;

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

        int ret = gpiod_line_event_wait(line_in, NULL);
        if (ret < 0) {
            perror("Error waiting for event");
            break;
        } else if (ret > 0) {
            // Read the event
            if (gpiod_line_event_read(line_in, &event) < 0) {
                perror("Error reading event");
                break;
            }
            // Check for falling edge event
            if (event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE) {
                impulse_count++;
                printf("Impulse detected! Total count: %d\n", impulse_count);
            }
        }

        time_t current_time = time(NULL); // Get the current time
        if (current_time >= start_time + INTERVAL_SEC) {
            printf("Pressed: %d\n", impulse_count);
            // Reset the counter
            impulse_count = 0;
            start_time = current_time; // Update the start time
            printf("Counter reset. Current time: %ld\n", current_time);
        }
        usleep(100000);  // 100ms
    }

    gpiod_chip_close(chip);
    return 0;
}
