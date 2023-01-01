#ifndef Pedal_hpp
#define Pedal_hpp

#include <stdint.h>

#include <MIDI.h>

#include "Contact.hpp"
#include "PedalsIO.hpp"

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

        explicit Pedal(const uint8_t number, const Function);

        void sendMidiEvent(const uint8_t midiChannel,
                           MidiInterface &,
                           PedalsIO &);

    private:
        enum class State
        {
            released = 0,
            depressed = 1
        };

        uint8_t number;
        
        Function function;

        Contact contact{};

        State previousState{State::released};

        State getActualState();

        void doSendMidiEvent(const uint8_t midiChannel,
                             MidiInterface &midiInterface,
                             const State);
    };
}

#endif