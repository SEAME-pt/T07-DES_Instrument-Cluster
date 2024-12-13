#pragma once
#include "Part.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

// template <typename T>
// std::string T::getPart() {
//     return _partName();
// }

class partBody : public Part {
    private:
        std::string _material;
    public:
        partBody();
        std::string getPart() const override;
        //void print_some() ;
        //void print(unsigned int i) override ;
};

class partBrake : public Part {
    public:
        partBrake();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override ;
};

class partChassis : public Part {
    public:
        partChassis();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override ;
};

class partDoor : public Part {
    public:
        partDoor();
        std::string getPart() const override;
        //void print() override ;
       // void print(unsigned int i) override ;
};

class partEngine : public Part {
    public:
        partEngine();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override ;
};

class partMediaSystem : public Part {
    public:
        partMediaSystem();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override ;
};

class partSeat : public Part {
    public:
        partSeat();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override ;
};

class partTire : public Part {
    public:
        partTire();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override ;
};

class partTransmission : public Part {
    public:
        partTransmission();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override ;
};

class partTrunk : public Part {
    public:
        partTrunk();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override ;
};

class partWheel : public Part {
    public:
        partWheel();
        std::string getPart() const override;
       // void print() override ;
        //void print(unsigned int i) override;
};

class partWindShield : public Part {
    public:
        partWindShield();
        std::string getPart() const override;
        //void print() override ;
        //void print(unsigned int i) override;
};
