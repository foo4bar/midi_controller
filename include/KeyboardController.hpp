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
        class Builder
        {
        public:
            uint8_t firstKeyMidiNoteNumber;
            uint8_t midiChannel;
            PedalsIO &pedalsIO;
            KeyboardMatricesIO &keyboardMatrices;
            MidiInterface &midiInterface;

            auto build() const
            {
                return KeyboardController{this->firstKeyMidiNoteNumber,
                                          this->midiChannel,
                                          this->pedalsIO,
                                          this->keyboardMatrices,
                                          this->midiInterface};
            }
        };

        void sendMidiEvents();

    private:
        KeyboardController(const uint8_t firstKeyMidiNoteNumber,
                           const uint8_t midiChannel,
                           PedalsIO &,
                           KeyboardMatricesIO &,
                           MidiInterface &);

        uint8_t firstKeyMidiNoteNumber;
        uint8_t midiChannel;
        PedalsIO &pedalsIO;
        KeyboardMatricesIO &keyboardMatrices;
        MidiInterface &midiInterface;

        std::vector<Pedal> pedals;

        std::vector<Key> keys;
    };

}

#endif