#include "MidiEventsGenerator.hpp"

namespace midi
{
    MidiEventsGenerator::MidiEventsGenerator()
    {
        {
            MIDI_CREATE_DEFAULT_INSTANCE()
            MIDI.begin(MIDI_CHANNEL_OMNI);
        }
    }

    void MidiEventsGenerator::generate(const std::array<kbd::Key, arduino::digital::numberOfScannedContactPairs> &keys) const
    {
        //TODO
    }
}