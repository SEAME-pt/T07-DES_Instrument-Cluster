
#pragma once

#include "ISensor.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <iostream>

class SpeedSensor : public ISensor {
    private:
        float lastSpeed;
        std::shared_ptr<spdlog::logger> file_logger;

    public:
        SpeedSensor(CANBus& can, uint32_t id);

        void initialize();
        int readData();
        const std::string getType() const;
};