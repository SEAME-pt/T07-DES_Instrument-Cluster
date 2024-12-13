#include "ISensor.hpp"
#include "SpeedSensor.hpp"
#include "CANBus/includes/CANBus.hpp"

int main() {

    CANBus canBus("vcan0", 500000);
    ISensor* sensor = new SpeedSensor(canBus, 0x100);
    while(1)
    {
        sensor->readData();
        std::cout << "Read from " << sensor->getType() << sensor->getValue() << std::endl;
    }
    delete sensor;
    return 0;
}