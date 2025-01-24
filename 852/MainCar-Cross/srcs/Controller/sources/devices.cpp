
#include <iostream>
#include "devices.hpp"


// toggle variables
bool isLightsLowOn = false;
bool isLightsHighOn = false;
bool isLightsLeftOn = false;
bool isLightsRightOn = false;
bool isLightsEmergencyOn = false;

void hornOnPressed(zmq::socket_t& pub)
{
    std::cout << "horn on\n";
    std::string message = "horn true";

    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}

void hornOnReleased(zmq::socket_t& pub)
{
    std::cout << "horn off\n";
    std::string message = "horn false";

    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}

void breakOnPressed(zmq::socket_t& pub)
{
    std::cout << "break on\n";
    std::string message = "break true";

    gpioWrite(GPIO_PIN_BREAK_LIGHTS, 0);

    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}

void breakOnReleased(zmq::socket_t& pub)
{
    std::cout << "break off\n";
    std::string message = "break false";

    gpioWrite(GPIO_PIN_BREAK_LIGHTS, 1);

    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}

void lightsLowToggle(zmq::socket_t& pub)
{
    // Change state
    isLightsLowOn = !isLightsLowOn;

    std::string state = isLightsLowOn ? "true" : "false";
    std::string message = "lightslow " + state;

     // GPIO SIGNAL
    if (isLightsLowOn) {
        gpioWrite(GPIO_PIN_LOW_LIGHTS, 0);
    } else {
        gpioWrite(GPIO_PIN_LOW_LIGHTS, 1);
    }

    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}

void lightsHighToggle(zmq::socket_t& pub)
{
    // Change state
    isLightsHighOn = !isLightsHighOn;

    std::string state = isLightsHighOn ? "true" : "false";
    std::string message = "lightshigh " + state;

    // GPIO SIGNAL
    if (isLightsHighOn) {
        gpioWrite(GPIO_PIN_HIGH_LIGHTS, 0); 
    } else {
        gpioWrite(GPIO_PIN_HIGH_LIGHTS, 1);
    }

    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}


void emergencyOnLights(zmq::socket_t& pub) {
    isLightsEmergencyOn = !isLightsEmergencyOn;

    std::string state = isLightsEmergencyOn ? "true" : "false";
    std::string message = "emergency " + state;

    if (isLightsEmergencyOn) {
        gpioWrite(GPIO_PIN_LEFT_LIGHTS, 0); // Liga o GPIO26
        gpioWrite(GPIO_PIN_RIGHT_LIGHTS, 0);
    } else {
        gpioWrite(GPIO_PIN_LEFT_LIGHTS, 1); // Desliga o GPIO26
        gpioWrite(GPIO_PIN_RIGHT_LIGHTS, 1);
    }

    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}

void indicationLightsRight(zmq::socket_t& pub) {
    // Toggle da luz direita
    isLightsRightOn = !isLightsRightOn;

    // Configure o estado como string para enviar via ZMQ
    std::string state = isLightsRightOn ? "true" : "false";
    std::string message = "lightsright " + state;

    // GPIO SIGNAL
    if (isLightsRightOn) {
        gpioWrite(GPIO_PIN_RIGHT_LIGHTS, 0); // Liga o GPIO26
    } else {
        gpioWrite(GPIO_PIN_RIGHT_LIGHTS, 1);
    }
    if (isLightsLeftOn) {
        gpioWrite(GPIO_PIN_LEFT_LIGHTS, 1);
    }

    // Envie a mensagem usando ZeroMQ
    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}

void indicationLightsLeft(zmq::socket_t& pub) {
    // Toggle da luz direita
    isLightsLeftOn = !isLightsLeftOn;

    // Configure o estado como string para enviar via ZMQ
    std::string state = isLightsLeftOn ? "true" : "false";
    std::string message = "lightsleft " + state;

    // GPIO SIGNAL
    if (isLightsLeftOn) {
        gpioWrite(GPIO_PIN_LEFT_LIGHTS, 0);
    } else {
        gpioWrite(GPIO_PIN_LEFT_LIGHTS, 1);
    }
    if (isLightsRightOn) {
        gpioWrite(GPIO_PIN_RIGHT_LIGHTS, 1);
    }

    // Envie a mensagem usando ZeroMQ
    auto result = pub.send(zmq::buffer(message), zmq::send_flags::none);
    if (result.has_value()) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message: " << message << std::endl;
    }
}
