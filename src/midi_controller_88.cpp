#include <midi_controller_88.hpp>
#include <MIDI.h>

using namespace std;

void setup()
{
    MIDI_CREATE_DEFAULT_INSTANCE();
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
}
