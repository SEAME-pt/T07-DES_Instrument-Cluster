#include "../includes/Part.hpp"

Part::Part() : _partName("Unknown") {}

Part::Part(const std::string partName) : _partName(partName) {}

Part::Part(const Part & original) : _partName(original._partName) {}

Part& Part::operator=(const Part& original) {
	if (this != &original) {
		_partName = original._partName;
	}
	return *this;
}

Part::~Part() {}

void Part :: print(void) {
    std::cout << getPart() << " part name ..." << std::endl;
}

void Part :: print(unsigned int i) {
    std::cout << getPart() << " ";
    switch (i)
    {
        case 0:
            std::cout << "LEFT FRONT = ";
            break;
        case 1:
            std::cout << "RIGHT FRONT = ";
            break;
        case 2:
            std::cout << "LEFT REAR = ";
            break;
        case 3:
            std::cout << "RIGHT REAR = ";
            break;
        default:
            break;
    }
    std::cout << " part name" << std::endl;

}

