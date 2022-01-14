#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <MIDI.h>

#include "Key.hpp"
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
            KeyboardMatricesIO *keyboardMatrices;
            MidiInterface *midiInterface;

            auto build() const
            {
                return KeyboardController{this->firstKeyMidiNoteNumber,
                                          this->midiChannel,
                                          this->keyboardMatrices,
                                          this->midiInterface};
            }
        };

        void sendMidiEvents();

    private:
        KeyboardController(const uint8_t firstKeyMidiNoteNumber,
                           const uint8_t midiChannel,
                           KeyboardMatricesIO *const,
                           MidiInterface *const);

        uint8_t firstKeyMidiNoteNumber;
        uint8_t midiChannel;
        KeyboardMatricesIO *keyboardMatrices;
        MidiInterface *midiInterface;

        std::vector<Key> keys;
    };

}

#endif