#include "Controller.hpp"

void onPressExample() {
    std::cout << "Button Pressed!" << std::endl;
}

void onReleaseExample() {
    std::cout << "Button Released!" << std::endl;
}

int main() {
    try {
        Controller controller;

        // Create actions for a button
        Actions buttonActions;
        buttonActions.onPress = onPressExample;
        buttonActions.onRelease = onReleaseExample;

        // Map the actions to the A button (SDL_CONTROLLER_BUTTON_A)
        controller.setButtonAction(SDL_CONTROLLER_BUTTON_A, buttonActions);

        // Start listening for gamepad events
        controller.listen();

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
