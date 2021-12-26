#include <MidiEventsGenerator.hpp>

namespace midi
{
    MidiEventsGenerator::MidiEventsGenerator()
    {
        {
            MIDI_CREATE_DEFAULT_INSTANCE();
            MIDI.begin(MIDI_CHANNEL_OMNI);
        }
    }

    void MidiEventsGenerator::generate(const std::vector<kbd::Key> &keys) const
    {
        //TODO
    }
}