#include "Midi.hpp"

namespace midictrl
{
    MIDI_CREATE_DEFAULT_INSTANCE()
    
    Midi::Midi()
    {
        {
            MIDI.begin(MIDI_CHANNEL_OMNI);
        }
    }

    void Midi::sendNoteOn(const uint8_t midiNoteNumber, const uint8_t keyVelocity) const
    {
        MIDI.sendNoteOn(midiNoteNumber, keyVelocity, midiChannel);
    }

    void Midi::sendNoteOff(const uint8_t midiNoteNumber, const uint8_t keyVelocity) const
    {
        MIDI.sendNoteOff(midiNoteNumber, keyVelocity, midiChannel);
    }
}