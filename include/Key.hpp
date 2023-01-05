#ifndef Key_hpp
#define Key_hpp

#include <MIDI.h>

#include "KeyContacts.hpp"

namespace kbd
{
    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class Key
    {
    public:
        void updateContactsState(const arduino::digital::KeyInputStates &);
        void sendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                           const uint8_t midiChannel,
                           MidiInterface &);

    private:
        enum class State
        {
            released = 0,
            depressed = 1,
            moving = 2
        };

        static inline constexpr uint8_t maxManipulationTimeMillis{250}; // TODO double check
        static inline constexpr uint8_t minVelocity{8};                 // pppp
        static inline constexpr uint8_t maxVelocity{127};               // ffff
        static inline constexpr uint8_t defaultVelocity{64};

        static inline constexpr double slope{static_cast<double>(minVelocity - maxVelocity) / maxManipulationTimeMillis};

        // Each key operates a pair of contacts.
        // One of them is closed first when a corresponding key starts to be pressed,
        // another one is closed last when the key is fully depressed.
        // Key state is defined by its contacts state.
        KeyContacts contacts;

        State previousState{State::released};
        uint8_t velocity{0};

        State getActualState();
        void doSendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                             const uint8_t midiChannel,
                             MidiInterface &midiInterface,
                             const State);
    };
}

#endif