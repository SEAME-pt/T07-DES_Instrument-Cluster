#include "SomeCar.hpp"
#include "ISensor.hpp"
#include "../cpp/modules/vehicle_speed/implementation/vehiclespeed.h" // Incluindo o cabeçalho do módulo VehicleSpeed
 
#include <iostream>
#include <string>
using namespace Cpp::VehicleSpeed;

class SpeedDisplay : public IVehicleSpeedSubscriber {
public:
    void onSpeedChanged(float speed) override {
        std::cout << "Speed updated on Cluster Display: " << speed << " m/h" << std::endl;
    }
};

class SpeedConsoleDisplay : public IVehicleSpeedSubscriber {
public:
    void onSpeedChanged(float speed) override {
        std::cout << "Speed updated on Cosole Display: " << speed << " m/h" << std::endl;
    }
};


int main() {

    // Inicialização do CANBus e sensor de velocidade (caso utilize)
    CANBus *canBus = new CANBus("vcan0", 500000);
    SpeedSensor *speedSensor = new SpeedSensor(*canBus, 0x100);

    // Inicialização de um carro
    SomeCar myCar("DeLorean", "DeLorean", 1981, 141);

    // Instancia a classe VehicleSpeed
    std::unique_ptr<Cpp::VehicleSpeed::VehicleSpeed> vehicleSpeed = std::make_unique<Cpp::VehicleSpeed::VehicleSpeed>();

    vehicleSpeed->setSpeed(88.0f);

    // Instancia a classe SpeedDisplay
    SpeedDisplay speedDisplay;
    SpeedConsoleDisplay speedConsoleDisplay;

    while(1)
    {
        vehicleSpeed->setSpeed(speedSensor->readData());
        speedDisplay.onSpeedChanged(vehicleSpeed->getSpeed());
        speedConsoleDisplay.onSpeedChanged(vehicleSpeed->getSpeed());
    }

    // Obtém a velocidade do veículo
    // std::cout << "Velocity is: " << vehicleSpeed->getSpeed() <<  "m/h\nYou are ready to back to the future: " << std::endl;

    // vehicleSpeed->setSpeed(speedSensor->readData());

    // std::cout << "Velocity is: " << vehicleSpeed->getSpeed() << " m/h" << std::endl;
    // Controlador para ler entradas
    // Controller controller("/dev/input/js0");
    // controller.listen();

    return 0;
}
