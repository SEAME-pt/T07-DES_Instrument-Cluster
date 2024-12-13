#include "JetSnailsCar.hpp"
#include <pigpio.h>
#include <thread>

void sensorsThreads(ISensor* sensor) {
    while(1)
    {
        sensor->read();
        std::cout << "Value from sensor: " << sensor->getType() << ": " << sensor->getValue() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {

    // CANBus canBus("vcan0", 500000);
    Controller controller;
    JetSnailsCar delorean;

    CANBus canBus("can0", 500000);
    ISensor* speedSensor = new SpeedSensor(canBus, 0x100);

    Actions buzzer;
    buzzer.onPress = activate_buzzer;
    buzzer.onRelease = deactivate_buzzer;
    controller.setButtonAction(SDL_CONTROLLER_BUTTON_A, buzzer);

    controller.setAxisAction(SDL_CONTROLLER_AXIS_LEFTX, steering);
    controller.setAxisAction(SDL_CONTROLLER_AXIS_RIGHTY, throttle);

    delorean.setController(&controller);
    
//    if (gpioInitialise() < 0) {
//        throw std::runtime_error("Failed to initialize pigpio library");
//    }

    std::thread drive(&JetSnailsCar::drive, &delorean);
    std::thread sensor1(sensorsThreads, speedSensor);
    drive.join();
    sensor1.join();
    
    return 0;
}
