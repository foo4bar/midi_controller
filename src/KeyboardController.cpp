#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController(const uint8_t firstKeyMidiNoteNumber,
                                           const uint8_t midiChannel,
                                           KeyboardMatricesIO &keyboardMatrices,
                                           MidiInterface &midiInterface) : firstKeyMidiNoteNumber{firstKeyMidiNoteNumber},
                                                                           midiChannel{midiChannel},
                                                                           keyboardMatrices{keyboardMatrices},
                                                                           midiInterface{midiInterface}

    {
        for (uint8_t keyNumber{0}; keyNumber < keyboardMatrices.getNumberOfKeysBeingScanned(); ++keyNumber)
        {
            this->keys.push_back(Key{keyNumber});
        }
    }

    void KeyboardController::sendMidiEvents()
    {
        for (auto &key : this->keys)
        {
            key.sendMidiEvent(this->firstKeyMidiNoteNumber,
                              this->midiChannel,
                              this->midiInterface,
                              this->keyboardMatrices);
        }
    }
}