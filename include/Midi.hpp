#ifndef Midi_hpp
#define Midi_hpp

#include <MIDI.h>

namespace midictrl
{
    class Midi
    {
    private:
        static inline constexpr uint8_t midiChannel{0};
        static inline constexpr uint8_t firstMidiNoteNumber{21};

        Midi();

    public:
        static inline const Midi &getIstance()
        {
            static const Midi instance;

            return instance;
        }

        static inline const uint8_t getActualMidiNoteNumber(const uint8_t zeroBasedNumber)
        {
            return firstMidiNoteNumber + zeroBasedNumber;
        }

        void sendNoteOn(const uint8_t midiNoteNumber, const uint8_t keyVelocity) const;

        void sendNoteOff(const uint8_t midiNoteNumber, const uint8_t keyVelocity) const;

        Midi(const Midi &) = delete;
        void operator=(const Midi &) = delete;
    };
}

#endif