#include <map>
#include <string>
#include <iostream>
#include "ConfigController.hpp"


ConfigController::ConfigController() {
    buttonActions = std::map<int, std::string>();
    axisActions = std::map<int, std::string>();
}

void ConfigController::setButtonAction(int button, const std::string& action) {
    buttonActions[button] = action;
}

void ConfigController::setAxisAction(int axis, const std::string& action) {
    axisActions[axis] = action;
}

std::string ConfigController::getButtonAction(int button) const {
    auto it = buttonActions.find(button);
    if (it != buttonActions.end()) {
        return it->second;
    }
    return "Unknown action";
}

std::string ConfigController::getAxisAction(int axis) const {
    auto it = axisActions.find(axis);
    if (it != axisActions.end()) {
        return it->second;
    }
    return "Unknown action";
}
