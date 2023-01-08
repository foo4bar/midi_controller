#ifndef Pedal_hpp
#define Pedal_hpp

#include <stdint.h>

#include <MIDI.h>

#include "Contact.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class Pedal
    {
    public:
        enum class Function : uint8_t
        {
            sustain = 64,
            sostenuto = 66,
            soft = 67
        };

        explicit Pedal(const Function, const arduino::digital::Pin &input);

        void sendMidiEvent(MidiInterface &);

        const Function function;

    private:
        enum class State
        {
            released = 0,
            depressed = 1
        };

        Contact contact{};

        const arduino::digital::Pin input;

        State previousState{State::released};

        State getActualState();

        void doSendMidiEvent(MidiInterface &midiInterface,
                             const State);
    };
}

#endif
