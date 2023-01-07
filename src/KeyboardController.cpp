#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController()
    {
#ifndef AVR_STUB_DEBUG
        this->midiInterface.begin(MIDI_CHANNEL_OMNI);
#endif
    }

    void KeyboardController::sendMidiEvents()
    {
        for (auto &pedal : this->pedals)
        {
            pedal.sendMidiEvent(this->midiInterface);
        }

        const auto keysInputsStates{KeyboardController::ioMatrices.getActualInstantaneousKeysInputsStates()};

        for (uint8_t keyNumber{0}; keyNumber < KeyboardController::ioMatrices.getNumberOfKeysBeingScanned(); ++keyNumber)
        {
            this->keys[keyNumber].sendMidiEvent(KeyboardController::firstKeyMidiNoteNumber + keyNumber,
                                                this->midiInterface,
                                                keysInputsStates[keyNumber]);
        }
    }
}