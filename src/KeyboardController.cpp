#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController()
    {
        for (uint8_t i = 0; i < this->numberOfKeys; i++)
        {
            this->keys.push_back(Key{i});
        }
    }

    void KeyboardController::sendMidiEvents()
    {
        for (auto &key : this->keys)
        {
            if (key.isSateChanged())
            {
                const uint8_t noteNumber = firstKeyMidiNoteNumber + key.getNumber();
                this->midiEventsSender.sendNoteEvent(noteNumber, key.getActualState(), key.getVelocity());
                key.resetStateChange();
            }
        }
    }
}