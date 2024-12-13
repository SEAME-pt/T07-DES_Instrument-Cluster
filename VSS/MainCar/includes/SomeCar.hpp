#pragma once

#include "ACar.hpp"
#include "partAll.hpp"
#include "ISensor.hpp"
#include "SpeedSensor.hpp"
#include "CANBus.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <vector>
#include <iostream>

class SomeCar : public ACar {
    private:
        int _maxSpeed;
        SpeedSensor *_speedSensor;
        

    public:
        SomeCar();
        SomeCar(const std::string& make, const std::string& model, const unsigned int year, const unsigned int maxSpeed);
        SomeCar(const SomeCar& other);
        SomeCar& operator=(const SomeCar& other);
        ~SomeCar();

        void readSensorsData() const;

        void setSpeedSensor(SpeedSensor *speedSensor);
};

std::ostream &  operator<<( std::ostream & o, SomeCar & i );
