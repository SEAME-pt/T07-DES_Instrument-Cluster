#pragma once

#include <iostream>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Part
{
    protected:
        std::string _partName;
    public:
        Part();
        Part(const std::string partName);
        Part(const Part & original);
        Part& operator=(const Part& original);
        virtual ~Part() = 0;

        virtual void print();
        virtual void print(unsigned int i);
        virtual std::string getPart() const = 0;
};
