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

        void sendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                           const uint8_t midiChannel,
                           MidiInterface &midiInterface);

    private:
        enum class State
        {
            depressed,
            released
        };

        static inline constexpr uint8_t maxManipulationTimeMillis{250}; //TODO double check
        static inline constexpr uint8_t minVelocity{8};                 //pppp
        static inline constexpr uint8_t maxVelocity{127};               //ffff
        static inline constexpr uint8_t defaultVelocity{64};

        static inline constexpr double slope{(minVelocity - maxVelocity) / maxManipulationTimeMillis};

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
        void doSendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                             const uint8_t midiChannel,
                             MidiInterface &midiInterface);
    };
}

#endif