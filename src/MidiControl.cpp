#include "MidiControl.hpp"

namespace midictrl
{
    MIDI_CREATE_DEFAULT_INSTANCE()

    MidiControl::MidiControl()
    {
        MIDI.begin(MIDI_CHANNEL_OMNI);
    }

    void MidiControl::sendNoteOn(const uint8_t midiNoteNumber, const uint8_t keyVelocity)
    {
        MIDI.sendNoteOn(midiNoteNumber, keyVelocity, MIDI_CHANNEL_OMNI);
    }

    void MidiControl::sendNoteOff(const uint8_t midiNoteNumber, const uint8_t keyVelocity)
    {
        MIDI.sendNoteOff(midiNoteNumber, keyVelocity, MIDI_CHANNEL_OMNI);
    }
}