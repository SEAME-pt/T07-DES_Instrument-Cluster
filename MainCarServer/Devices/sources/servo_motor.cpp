#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include "devices.hpp"

const int STEERING_CHANNEL = 0;

// Servo configuration
const int MAX_ANGLE = 180;
const int SERVO_CENTER_PWM = 330;
const int SERVO_LEFT_PWM = 80;
const int SERVO_RIGHT_PWM = 580;

int servo_handle;

void initializeServo() {
    servo_handle = i2cOpen(1, SERVO_ADDR, 0);

    if (servo_handle < 0 || motor_handle < 0) {
        gpioTerminate();
        throw std::runtime_error("Failed to initialize I2C devices");
    }

    // Initialize servo
    i2cWriteByteData(servo_handle, 0x00, 0x10);
    usleep(100000);
    i2cWriteByteData(servo_handle, 0xFE, 0x79); // Set ~50Hz
    i2cWriteByteData(servo_handle, 0x00, 0x20);

}

void setServoAngle(int angle) {
    angle = std::max(-MAX_ANGLE, std::min(MAX_ANGLE, angle));
    int pwm;
    if (angle < 0) {
        pwm = SERVO_CENTER_PWM + (angle / (float)MAX_ANGLE) * (SERVO_CENTER_PWM - SERVO_LEFT_PWM);
    } else if (angle > 0) {
        pwm = SERVO_CENTER_PWM + (angle / (float)MAX_ANGLE) * (SERVO_RIGHT_PWM - SERVO_CENTER_PWM);
    } else {
        pwm = SERVO_CENTER_PWM;
    }
    setPWM(servo_handle, STEERING_CHANNEL, 0, pwm);
}
