#ifndef Key_hpp
#define Key_hpp

#include <MIDI.h>

#include "ContactPair.hpp"

namespace kbd
{
    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class Key
    {
    public:
        enum class State
        {
            depressed,
            halfReleased,
            released
        };

        Key(const uint8_t, MidiInterface *const);

        void sendMidiEvent(const uint8_t, const uint8_t);

    private:
        // Each key operates a pair of contacts.
        // One of them is closed first when a corresponding key starts to be pressed,
        // another one is closed last when the key is fully depressed.
        // Key state is defined by its contacts state.
        ContactPair contacts;

        MidiInterface *const midiInterface;

        State previousState{State::released};
        State actualState{State::released};
        uint8_t velocity{0};

        void updateActualState();
    };
}

#endif