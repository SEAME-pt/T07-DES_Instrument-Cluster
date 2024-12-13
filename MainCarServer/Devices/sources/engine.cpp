
#include "devices.hpp"

int motor_handle;

void initializeMotors() {    
    motor_handle = i2cOpen(1, MOTOR_ADDR, 0);

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

void setMotorSpeed(int speed) {
    speed = std::max(-100, std::min(100, speed));
    int pwm_value = static_cast<int>(std::abs(speed) / 100.0 * 4095);

    if (speed > 0) { // Movimento para frente
        setPWM(motor_handle, 0, 0, pwm_value); // IN1
        setPWM(motor_handle, 1, 0, 0);         // IN2
        setPWM(motor_handle, 2, 0, pwm_value); // ENA
        setPWM(motor_handle, 5, 0, pwm_value); // IN3
        setPWM(motor_handle, 6, 0, 0);         // IN4
        setPWM(motor_handle, 7, 0, pwm_value); // ENB
    } else if (speed < 0) {
        setPWM(motor_handle, 0, 0, pwm_value);      // IN1 (Desativa)
        setPWM(motor_handle, 1, 0, pwm_value);      // IN2 (Ativa para reverso)
        setPWM(motor_handle, 2, 0, 0);              // ENA (Ativa o motor 1 para reverso)
    
        setPWM(motor_handle, 6, 0, pwm_value);      // IN3 (Ativa para reverso)
        setPWM(motor_handle, 7, 0, pwm_value);      // IN4 (Desativa)
        setPWM(motor_handle, 8, 0, 0);              // ENB (Ativa o motor 2 para reverso)
    } else { // Stop
        for (int channel = 0; channel < 9; ++channel) {
            setPWM(motor_handle, channel, 0, 0);
        }
    }
}