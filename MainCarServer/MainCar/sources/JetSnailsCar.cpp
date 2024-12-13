#include "JetSnailsCar.hpp"

// Constructors
JetSnailsCar::JetSnailsCar() : ACar(), _maxSpeed(0) {
    std::cout << "Default constructor called for JetSnailsCar" << std::endl;
}

JetSnailsCar::JetSnailsCar(const std::string& make, const std::string& model, const unsigned int year, const unsigned int maxSpeed)
    : ACar(make, model, year), _maxSpeed(maxSpeed) {
    std::cout << "Parameterized constructor called for JetSnailsCar: " << make << " " << model << " " << year << " " << maxSpeed << std::endl;
}

JetSnailsCar::JetSnailsCar(const JetSnailsCar& original) : ACar(original), _maxSpeed(original._maxSpeed) {
    std::cout << "Copy constructor called for JetSnailsCar" << std::endl;
}

// Destructor
JetSnailsCar::~JetSnailsCar() {
    std::cout << "Destructor called for JetSnailsCar" << std::endl;
}

// Member function
void JetSnailsCar::drive() const {
    _controller->listen();
}

void JetSnailsCar::printParts(void) const {
    std::cout << "Print parts goes here!" << std::endl;
}

void JetSnailsCar::printSensors(void) const {
    std::cout << "Print Sensors goes here!" << std::endl;
}


// void JetSnailsCar::setSpeedSensor(SpeedSensor *speedSensor) {
//     _speedSensor = speedSensor;
// }

void JetSnailsCar::setController(Controller *controller) {
    _controller = controller;
}

// Operator overload
JetSnailsCar& JetSnailsCar::operator=(const JetSnailsCar& original) {
    if (this != &original) {
        ACar::operator=(original);
        _maxSpeed = original._maxSpeed;
    }
    std::cout << "Copy assignment operator called for JetSnailsCar" << std::endl;
    return *this;
}
