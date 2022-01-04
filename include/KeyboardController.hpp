#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <MIDI.h>

#include "Key.hpp"

namespace kbd
{
    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class KeyboardController
    {
    private:
        KeyboardController(const uint8_t, const uint8_t, const uint8_t, MidiInterface *const);

        uint8_t firstKeyMidiNoteNumber;
        uint8_t midiChannel;
        MidiInterface *midiInterface;

        std::vector<Key> keys;

    public:
        class Builder
        {
        private:
            uint8_t firstKeyMidiNoteNumber;
            uint8_t midiChannel;
            uint8_t numberOfKeys;
            MidiInterface *midiInterface;

        public:
            Builder &withfirstKeyMidiNoteNumber(const uint8_t firstKeyMidiNoteNumber)
            {
                this->firstKeyMidiNoteNumber = firstKeyMidiNoteNumber;
                return *this;
            }

            Builder &withMidiChannel(const uint8_t midiChannel)
            {
                this->midiChannel = midiChannel;
                return *this;
            }

            Builder &withNumberOfKeys(const uint8_t numberOfKeys)
            {
                this->numberOfKeys = numberOfKeys;
                return *this;
            }

            Builder &withMidiInterface(MidiInterface *const midiInterface)
            {
                this->midiInterface = midiInterface;
                return *this;
            }

            KeyboardController build() const
            {
                return KeyboardController{this->firstKeyMidiNoteNumber,
                                          this->midiChannel,
                                          this->numberOfKeys,
                                          this->midiInterface};
            }
        };

        void sendMidiEvents();
    };
}

#endif