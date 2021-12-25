#include <MIDI.h>
#include <KeyboardController.hpp>

using namespace std;

void setup()
{
    MIDI_CREATE_DEFAULT_INSTANCE();
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
    const kbd::KeyboardController controller;
}
