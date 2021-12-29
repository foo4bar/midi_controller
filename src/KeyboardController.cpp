#include "KeyboardController.hpp"

namespace kbd
{
    void KeyboardController::sendMidiEvents()
    {
        uint8_t counter{0};
        for (auto &key : this->keys)
        {   
            if (key.isSateChanged())
            {
                const uint8_t noteNumber = firstKeyMidiNoteNumber + counter;
                this->midiEventsSender.generate(noteNumber, key.getActualState(), key.velocity);
                key.resetStateChange();
            }

            counter++;
        }
    }
}