#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController(const uint8_t firstKeyMidiNoteNumber,
                                           const uint8_t midiChannel,
                                           const uint8_t numberOfKeys) : firstKeyMidiNoteNumber{firstKeyMidiNoteNumber},
                                                                                 midiChannel{midiChannel}
    {
        for (uint8_t keyNumber{0}; keyNumber < numberOfKeys; ++keyNumber)
        {
            this->keys.push_back(kbd::Key{keyNumber});
        }
    }

    void KeyboardController::sendMidiEvents(MidiInterface &midiInterface)
    {
        for (auto &key : this->keys)
        {
            key.sendMidiEvent(this->firstKeyMidiNoteNumber, this->midiChannel, midiInterface);
        }
    }
}