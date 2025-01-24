#include "JetCar.hpp"
#include <unistd.h>
#include <cmath>         // For std::abs, std::floor, etc.
#include <stdexcept>     // For std::runtime_error
#include <algorithm>     // For std::max, std::min
#include <pigpio.h>      // For pigpio functions like i2cOpen, gpioInitialise, etc.


//div 16535 , 165

void JetCar::setPWM(int device_handle, int channel, int on_value, int off_value) {
    int reg_base = 0x06 + (channel * 4);
    i2cWriteByteData(device_handle, reg_base, on_value & 0xFF);
    i2cWriteByteData(device_handle, reg_base + 1, on_value >> 8);
    i2cWriteByteData(device_handle, reg_base + 2, off_value & 0xFF);
    i2cWriteByteData(device_handle, reg_base + 3, off_value >> 8);
}

void JetCar::setServoAngle(int angle) {
    angle = std::max(-MAX_ANGLE, std::min(45, angle));
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

void JetCar::setMotorSpeed(int speed) {
    speed = std::max(-100, std::min(100, speed));
    int pwm_value = static_cast<int>(std::abs(speed) / 100.0 * 4095);

    if (speed > 0) { // Forward
        setPWM(motor_handle, 1, pwm_value, 0); // IN1
        setPWM(motor_handle, 2, 0, pwm_value); // IN2
        setPWM(motor_handle, 0, 0, pwm_value); // ENA


        setPWM(motor_handle, 5, 0, pwm_value); // IN3
        setPWM(motor_handle, 6, pwm_value, 0);         // IN4
        setPWM(motor_handle, 7, 0, pwm_value); // ENB
    } else if (speed < 0) { // Backward
        setPWM(motor_handle, 0, 0, pwm_value); // ENA
        setPWM(motor_handle, 1, 0, pwm_value); // IN1
        setPWM(motor_handle, 2, pwm_value, 0);         // IN2

       setPWM(motor_handle, 5, pwm_value, 0);         // IN3
       setPWM(motor_handle, 6, 0, pwm_value); // IN4
       setPWM(motor_handle, 7, 0, pwm_value); // ENB

    } else { // Stop
        for (int channel = 0; channel < 8; ++channel) {
            setPWM(motor_handle, channel, 0, 0);
        }
    }
}

JetCar::JetCar() {
    if (gpioInitialise() < 0) {
        throw std::runtime_error("Failed to initialize pigpio library");
    }

    servo_handle = i2cOpen(1, SERVO_ADDR, 0);
    motor_handle = i2cOpen(1, MOTOR_ADDR, 0);

    if (servo_handle < 0 || motor_handle < 0) {
        gpioTerminate();
        throw std::runtime_error("Failed to initialize I2C devices");
    }

    // Initialize servo
    i2cWriteByteData(servo_handle, 0x00, 0x10);
    usleep(100000);
    i2cWriteByteData(servo_handle, 0xFE, 0x79); // Set ~50Hz
    i2cWriteByteData(servo_handle, 0x00, 0x20);

    // Initialize motor
    i2cWriteByteData(motor_handle, 0x00, 0x20);
    int prescale = std::floor(25000000.0 / 4096.0 / 60.0 - 1);
    int oldmode = i2cReadByteData(motor_handle, 0x00);
    int newmode = (oldmode & 0x7F) | 0x10;
    i2cWriteByteData(motor_handle, 0x00, newmode);
    i2cWriteByteData(motor_handle, 0xFE, prescale);
    i2cWriteByteData(motor_handle, 0x00, oldmode);
    usleep(5000);
    i2cWriteByteData(motor_handle, 0x00, oldmode | 0xA1);
}

JetCar::~JetCar() {
    i2cClose(servo_handle);
    i2cClose(motor_handle);
    gpioTerminate();
}

void JetCar::sequence() {
    setMotorSpeed(100);
    sleep(2);

    setMotorSpeed(-100);
    sleep(2);

    setMotorSpeed(0);

    setServoAngle(-45);
    sleep(1);

    setServoAngle(45);
    sleep(1);

    setServoAngle(0);
    setMotorSpeed(0);
}

