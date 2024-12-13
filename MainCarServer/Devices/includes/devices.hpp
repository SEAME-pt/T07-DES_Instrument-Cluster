#pragma once

#include <iostream>
#include <pigpio.h>
#include <stdexcept> // std::runtime_error


#define BUZZER_PIN 17 // GPIO17

#define SERVO_ADDR 0x40
#define MOTOR_ADDR 0x60

//#Buzzer
void activate_buzzer();
void deactivate_buzzer();

//#Engines
void setPWM(int device_handle, int channel, int on_value, int off_value);
void setServoAngle(int angle);
void setMotorSpeed(int speed);
void initializeMotors();
void initializeServo();

void steering(int value);
void throttle(int value);
