#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController(const uint8_t firstKeyMidiNoteNumber,
                                           const uint8_t midiChannel,
                                           const uint8_t numberOfKeys,
                                           MidiInterface *const midiInterface) : firstKeyMidiNoteNumber{firstKeyMidiNoteNumber},
                                                                                 midiChannel{midiChannel},
                                                                                 midiInterface{midiInterface}
    {
        for (uint8_t keyNumber{0}; keyNumber < numberOfKeys; ++keyNumber)
        {
            this->keys.push_back(kbd::Key{keyNumber});
        }
    }

    void KeyboardController::sendMidiEvents()
    {
        for (auto &key : this->keys)
        {
            key.sendMidiEvent(this->firstKeyMidiNoteNumber, this->midiChannel, this->midiInterface);
        }
    }
}