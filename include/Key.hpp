#ifndef Key_hpp
#define Key_hpp

#include <stdint.h>

#include <MIDI.h>

#include "KeyContacts.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class Key
    {
    public:
        void sendMidiEvent(const uint8_t midiNoteNumber,
                           MidiInterface &,
                           const arduino::digital::KeyInputStates &);

    private:
        enum class State : uint8_t
        {
            released = 0,
            depressed = 1,
            moving = 2
        };

        static inline constexpr uint8_t maxManipulationTimeMillis{250}; // To be adjusted empirically.
        static inline constexpr uint8_t minVelocity{8};                 // pppp
        static inline constexpr uint8_t maxVelocity{127};               // ffff
        static inline constexpr uint8_t noteOffVelocity{64};            // It may be any as it doesn't matter for piano.

        static inline constexpr double slope{static_cast<double>(Key::minVelocity - Key::maxVelocity) / Key::maxManipulationTimeMillis};

        KeyContacts contacts;

        State previousState{State::released};
        uint8_t velocity{0};

        State getActualState();
        void doSendMidiEvent(const uint8_t midiNoteNumber,
                             MidiInterface &midiInterface,
                             const State);
    };
}

#endif