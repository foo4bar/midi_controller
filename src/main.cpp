#include "KeyboardController.hpp"

kbd::KeyboardController keyboardController;

void setup()
{
    //Empty definition. There's nothing to setup globally.
}

void loop()
{
    keyboardController.sendMidiEvents();
}
