#include "MidiEventsGenerator.hpp"
#include "KeyboardController.hpp"

using namespace std;

inline const midi::MidiEventsGenerator midiGenerator{};

kbd::KeyboardController keyboardController{};

void setup()
{
    //Empty definition. There's nothing to setup.
}

void loop()
{
    midiGenerator.generate(keyboardController.updateKeysStateAndGet());
}
