#include <MIDI.h>

#include "MidiEventsSender.hpp"

namespace midictrl
{
    MIDI_CREATE_DEFAULT_INSTANCE()

    MidiEventsSender::MidiEventsSender()
    {
        {
            MIDI.begin(MIDI_CHANNEL_OMNI);
        }
    }

    void MidiEventsSender::generate(const uint8_t midiNoteNumber,
                                    const kbd::Key::State &actualKeyState,
                                    const uint8_t keyVelocity) const
    {
        switch (actualKeyState)
        {
        case kbd::Key::State::depressed:
            MIDI.sendNoteOn(midiNoteNumber, keyVelocity, midiChannel);
            break;
        case kbd::Key::State::released:
            MIDI.sendNoteOff(midiNoteNumber, keyVelocity, midiChannel);
            break;
        case kbd::Key::State::halfPressed:
            //Nothing to do here.
            //1. If the key was released before, then no event should be generated till it's fully depressed.
            //2. If the key was depressed before, then sound shouldn't be damped to emulate repetition
            //   in the case if the key goes again from the state to the depressed state.
            break;
        default:
            break;
        }
    }
}