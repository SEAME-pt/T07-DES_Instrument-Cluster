#include "Controller.hpp"

// Constructor: Initializes the joystick controller
Controller::Controller(const std::string& devicePath, ConfigController& config) : fd(-1), configController(config) {
    file_logger = spdlog::basic_logger_mt("Joypad", "joypad.log");
    fd = open(devicePath.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("Error opening joystick device");
        throw std::runtime_error("Unable to open the joystick device.");
    }

    // Attempt to retrieve the joystick's name
    char name[128];
    if (ioctl(fd, JSIOCGNAME(sizeof(name)), name) < 0) {
        std::cerr << "Unable to retrieve the joystick name." << std::endl;
    } else {
        std::cout << "Joystick connected: " << name << std::endl;
    }
}

// Destructor: Ensures the file descriptor is closed
Controller::~Controller() {
    if (fd >= 0) {
        close(fd);
    }
}

// Listen for joystick events and process them
// Listen for joystick events
void Controller::listen() {
    struct js_event event;
    int exit = 0;
    while (!exit) {
        ssize_t bytes = read(fd, &event, sizeof(event));
        if (bytes == sizeof(event)) {
            exit = processEvent(event);
        } else if (bytes < 0 && errno != EAGAIN) {
            perror("Error reading joystick events");
            break;
        }
        usleep(1000); // Sleep to prevent high CPU usage
    }
}

// Process joystick events
int Controller::processEvent(const struct js_event& event) {
    if (event.type & JS_EVENT_BUTTON) {
        if (event.number < buttonStates.size()) {
            buttonStates[event.number] = (event.value != 0);
            // Consultar a ação configurada para este botão
            std::string action = configController.getButtonAction(event.number);
            if (event.value != 0) {
                std::cout << "Button " << event.number << " pressed: " << action << std::endl;
            } else {
                std::cout << "Button " << event.number << " released: " << action << std::endl;
            }
        }
    } else if (event.type & JS_EVENT_AXIS) {
        if (event.number == 0) { // Steering axis
            steeringValue = event.value;
            // Consultar a ação configurada para este eixo
            std::string action = configController.getAxisAction(event.number);
            std::cout << "Axis " << event.number << " moved (Steering): " << event.value << " -> " << action << std::endl;
        } else if (event.number == 1) { // Throttle axis
            throttleValue = event.value;
            // Consultar a ação configurada para este eixo
            std::string action = configController.getAxisAction(event.number);
            std::cout << "Axis " << event.number << " moved (Throttle): " << event.value << " -> " << action << std::endl;
        }
    }

}

// Get throttle value
int Controller::getThrottleValue() const {
    return throttleValue;
}

// Get steering value
int Controller::getSteeringValue() const {
    return steeringValue;
}

// Get button map
std::array<bool, 20> Controller::getButtonMap() const {
    return buttonStates;
}