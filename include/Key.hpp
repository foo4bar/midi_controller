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
        Key(const uint8_t);

        void sendMidiEvent(const uint8_t, const uint8_t, MidiInterface &);

    private:
        enum class State
        {
            depressed,
            halfReleased,
            released
        };

        static inline constexpr uint8_t maxPressingTimeMillis{250}; //TODO double check
        static inline constexpr uint8_t minVelocity{10};            //TODO double check
        static inline constexpr uint8_t maxVelocity{120};           //TODO double check

        uint8_t number;

        // Each key operates a pair of contacts.
        // One of them is closed first when a corresponding key starts to be pressed,
        // another one is closed last when the key is fully depressed.
        // Key state is defined by its contacts state.
        ContactPair contacts;

        State previousState{State::released};
        State actualState{State::released};
        uint8_t velocity{0};

        void updateActualState();
    };
}

#endif