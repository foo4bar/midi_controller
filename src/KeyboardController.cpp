#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController(const PedalsIO &pedalsIO,
                                           const KeyboardMatricesIO &keyboardMatricesIO,
                                           MidiInterface &midiInterface) : pedalsIO{pedalsIO},
                                                                           keyboardMatricesIO{keyboardMatricesIO},
                                                                           midiInterface{midiInterface}

    {
        for (uint8_t keyNumber{0}; keyNumber < keyboardMatricesIO.getNumberOfKeysBeingScanned(); ++keyNumber)
        {
            this->keys.push_back(Key{keyNumber});
        }
    }

    void KeyboardController::sendMidiEvents()
    {
        for (auto &pedal : this->pedals)
        {
            pedal.sendMidiEvent(this->midiChannel,
                                this->midiInterface,
                                this->pedalsIO);
        }

        for (auto &key : this->keys)
        {
            key.sendMidiEvent(this->firstKeyMidiNoteNumber,
                              this->midiChannel,
                              this->midiInterface,
                              this->keyboardMatricesIO);
        }
    }
}