#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <MIDI.h>

#include "Key.hpp"

namespace kbd
{
    class Key;

    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class KeyboardController
    {
    private:
        KeyboardController(const uint8_t firstKeyMidiNoteNumber,
                           const uint8_t midiChannel,
                           const uint8_t numberOfKeys);

        uint8_t firstKeyMidiNoteNumber;
        uint8_t midiChannel;

        std::vector<Key> keys;

    public:
        class Builder
        {
        public:
            uint8_t firstKeyMidiNoteNumber;
            uint8_t midiChannel;
            uint8_t numberOfKeys;

            auto build() const
            {
                return KeyboardController{this->firstKeyMidiNoteNumber,
                                          this->midiChannel,
                                          this->numberOfKeys};
            }
        };

        void sendMidiEvents(MidiInterface &);
    };
}

#endif