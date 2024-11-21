#include "speed.h"
#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int speed() {
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


    // while (1) {
    //     // Ler o estado do pino (HIGH ou LOW)
    //     int value = gpiod_line_get_value(line_in);

    //     if (value < 0) {
    //         printf("Erro to read pin value\n");
    //         break;
    //     }

	// printf("value: %d\n", value);
    //     // Verifique se o pino está em LOW (pressionado)
    //     if (value == 0) {
    //         printf("Pressed\n");
	//     gpiod_line_set_value(line_out, 0); 
    //     } else {
	//     gpiod_line_set_value(line_out, 1); 
    //         printf("Not Pressed\n");
    //     }

    //     usleep(100000);  // 100ms
    // }

    // gpiod_chip_close(chip);
    return 0;
}

