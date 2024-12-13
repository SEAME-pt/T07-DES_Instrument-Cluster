#include "devices.hpp"

//void setPWM(int device_handle, int channel, int on_value, int off_value) {
//    int reg_base = 0x06 + (channel * 4);
 //   i2cWriteByteData(device_handle, reg_base, on_value & 0xFF);
  //  i2cWriteByteData(device_handle, reg_base + 1, on_value >> 8);
  //  i2cWriteByteData(device_handle, reg_base + 2, off_value & 0xFF);
  //  i2cWriteByteData(device_handle, reg_base + 3, off_value >> 8);
//}

// # BUZZER
void activate_buzzer() {
//    gpioSetMode(BUZZER_PIN, PI_OUTPUT); // Set BUZZER_PIN as output
//    gpioWrite(BUZZER_PIN, 1); // Turn the buzzer ON
    std::cout << "Buzzer turned on." << std::endl;
}

void deactivate_buzzer() {
//    gpioSetMode(BUZZER_PIN, PI_OUTPUT); // Set BUZZER_PIN as output
//    gpioWrite(BUZZER_PIN, 0); // Turn the buzzer OFF

    std::cout << "Buzzer turned off." << std::endl;
}

void steering(int value) {
    std::cout << "Steering: " << value << std::endl;
}

void throttle(int value) {
    std::cout << "Throttle: " << value << std::endl;
}

// int main() {
//     try {
//         initMotorController();

//         std::cout << "Acelerando para frente..." << std::endl;
//         setMotorSpeed(50); // Velocidade para frente
//         gpioDelay(2000000); // 2 segundos

//         std::cout << "Acelerando para trás..." << std::endl;
//         setMotorSpeed(-50); // Velocidade para trás
//         gpioDelay(2000000); // 2 segundos

//         std::cout << "Parando..." << std::endl;
//         setMotorSpeed(0); // Parar
//         gpioDelay(2000000); // 2 segundos

//     } catch (const std::exception& e) {
//         std::cerr << "Erro: " << e.what() << std::endl;
//     }

//     cleanupMotorController();
//     return 0;
// }
