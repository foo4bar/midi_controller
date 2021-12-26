#include <MidiEventsGenerator.hpp>

#include "KeyboardController.hpp"

using namespace std;

inline const kbd::KeyboardController controller{};
inline const midi::MidiEventsGenerator midiGenerator{};

void setup()
{
    //Empty definition.
}

void loop()
{
    midiGenerator.generate(controller.getKeys());
}
