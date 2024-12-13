#include "../includes/partAll.hpp"

/*********************************************** */
partBody::partBody() : Part("Body"){this->_material = "Steel";}

std::string partBody::getPart() const {
    return (_partName);
}

/*********************************************** */
partBrake::partBrake() : Part("Brake") {}

std::string partBrake::getPart() const {
    return (_partName);
}

/*********************************************** */
partChassis::partChassis() : Part("Chassis") {}

std::string partChassis::getPart() const {
    return (_partName);
}

/*********************************************** */
partDoor::partDoor() : Part("Door") {}

std::string partDoor::getPart() const {
    return (_partName);
}

/*********************************************** */
partEngine::partEngine() : Part("Engine") {}

std::string partEngine::getPart() const {
    return (_partName);
}

/*********************************************** */
partMediaSystem::partMediaSystem() : Part("Media System") {}

std::string partMediaSystem::getPart() const {
    return (_partName);
}

/*********************************************** */
partSeat::partSeat() : Part("Seat") {}

std::string partSeat::getPart() const {
    return (_partName);
}

/*********************************************** */
partTire::partTire() : Part("Tire") {}

std::string partTire::getPart() const {
    return (_partName);
}

/*********************************************** */
partTransmission::partTransmission() : Part("Transmission") {}

std::string partTransmission::getPart() const {
    return (_partName);
}

/*********************************************** */
partTrunk::partTrunk() : Part("Trunk") {}

std::string partTrunk::getPart() const {
    return (_partName);
}

/*********************************************** */
partWheel::partWheel() : Part("Wheel") {}

std::string partWheel::getPart() const {
    return (_partName);
}

/*********************************************** */
partWindShield::partWindShield() : Part("Wind Shield") {}

std::string partWindShield::getPart() const {
    return (_partName);
}