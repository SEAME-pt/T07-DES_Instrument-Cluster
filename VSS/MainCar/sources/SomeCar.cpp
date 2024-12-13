#include "SomeCar.hpp"
#include "partAll.hpp"

// Constructors
SomeCar::SomeCar() : ACar(), _maxSpeed(0) {
    std::cout << "Default constructor called for SomeCar" << std::endl;
}

SomeCar::SomeCar(const std::string& make, const std::string& model, const unsigned int year, const unsigned int maxSpeed)
    : ACar(make, model, year), _maxSpeed(maxSpeed) {
    std::cout << "Parameterized constructor called for SomeCar: " << make << " " << model << " " << year << " " << maxSpeed << std::endl;
}

SomeCar::SomeCar(const SomeCar& original) : ACar(original), _maxSpeed(original._maxSpeed) {
    std::cout << "Copy constructor called for SomeCar" << std::endl;
}

// Destructor
SomeCar::~SomeCar() {
    std::cout << "Destructor called for SomeCar" << std::endl;
}

void SomeCar::readSensorsData(void) const {
    _speedSensor->readData();
}

void SomeCar::setSpeedSensor(SpeedSensor *speedSensor) {
    _speedSensor = speedSensor;
}

// Operator overload
SomeCar& SomeCar::operator=(const SomeCar& original) {
    if (this != &original) {
        ACar::operator=(original);
        _maxSpeed = original._maxSpeed;
    }
    std::cout << "Copy assignment operator called for SomeCar" << std::endl;
    return *this;
}
