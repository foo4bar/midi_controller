#include <MidiEventsGenerator.hpp>

#include "KeyboardController.hpp"

using namespace std;

inline const kbd::KeyboardController keyboardController{};
inline const midi::MidiEventsGenerator midiGenerator{};

void setup()
{
    //Empty definition. There's nothing to setup.
}

void loop()
{
    midiGenerator.generate(keyboardController.getKeys());
}
