#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController(const std::vector<Key> &keys) : keys{keys} {}

    void KeyboardController::sendMidiEvents()
    {
        for (auto &key : this->keys)
        {
            key.sendMidiEvent(firstKeyMidiNoteNumber, midiChannel);
        }
    }
}