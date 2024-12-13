#pragma once

#include "ACar.hpp"
#include "Controller.hpp"
#include "devices.hpp"
#include "ISensor.hpp"
#include "SpeedSensor.hpp"
//#include "CANBus.hpp"

#include <vector>
#include <iostream>

class JetSnailsCar : public ACar {
    private:
        int _maxSpeed;
        Controller *_controller;

    public:
        JetSnailsCar();
        JetSnailsCar(const std::string& make, const std::string& model, const unsigned int year, const unsigned int maxSpeed);
        JetSnailsCar(const JetSnailsCar& other);
        JetSnailsCar& operator=(const JetSnailsCar& other);
        ~JetSnailsCar();

        void drive() const;
        void printParts() const;
        void printSensors() const;

        void setController(Controller *controller);
};

std::ostream &  operator<<( std::ostream & o, JetSnailsCar & i );
