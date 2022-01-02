#ifndef MidiControl_hpp
#define MidiControl_hpp

#include <HardwareSerial.h>
#include <MIDI.h>

namespace midictrl
{
    class MidiControl
    {
    private:
        static inline constexpr uint8_t firstMidiNoteNumber{21};

        MidiControl();

    public:
        static inline const MidiControl &getIstance()
        {
            static const MidiControl instance;

            return instance;
        }

        MidiControl(const MidiControl &) = delete;
        void operator=(const MidiControl &) = delete;

        static inline const uint8_t getActualMidiNoteNumber(const uint8_t zeroBasedNumber)
        {
            return firstMidiNoteNumber + zeroBasedNumber;
        }

        static void sendNoteOn(const uint8_t, const uint8_t);

        static void sendNoteOff(const uint8_t, const uint8_t);
    };
}

#endif