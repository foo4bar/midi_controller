#include "KeyboardController.hpp"

void setup()
{
    //Empty definition.
}

void loop()
{
    kbd::KeyboardController::getInstance()
        .sendMidiEvents();
}
