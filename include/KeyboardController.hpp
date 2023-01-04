#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <MIDI.h>

#include "Key.hpp"
#include "Pedal.hpp"
#include "KeyboardMatricesIO.hpp"

namespace kbd
{
    class Key;

    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class KeyboardController
    {
    public:
        KeyboardController(const PedalsIO &,
                           const KeyboardMatricesIO &,
                           MidiInterface &);

        void sendMidiEvents();

    private:
        uint8_t firstKeyMidiNoteNumber{21};
        uint8_t midiChannel{1};
        const PedalsIO &pedalsIO;
        const KeyboardMatricesIO &keyboardMatricesIO;
        MidiInterface &midiInterface;

        std::vector<Pedal> pedals{Pedal{Pedal::Function::soft},
                                  Pedal{Pedal::Function::sostenuto},
                                  Pedal{Pedal::Function::sustain}};

        std::vector<Key> keys;
    };

}

#endif