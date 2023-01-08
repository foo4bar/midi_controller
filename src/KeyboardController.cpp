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

    std::vector<KeyGroupOutputs> KeyboardController::initKeyGroupsOutputs(const std::vector<uint8_tPair> &pinsNumbers)
    {
        std::vector<KeyGroupOutputs> result;

        for (const auto &[first, last] : pinsNumbers)
        {
            const Pin firstActuatedKeyContactOutput{first, Mode::output, State::high};
            const Pin lastActuatedKeyContactOutput{last, Mode::output, State::high};

            result.push_back(KeyGroupOutputs{firstActuatedKeyContactOutput, lastActuatedKeyContactOutput});
        }

        return result;
    }

    std::vector<Pin> KeyboardController::initInputs(const std::vector<uint8_t> &pinsNumbers)
    {
        std::vector<Pin> result;

        for (const uint8_t pinNumber : pinsNumbers)
        {
            result.push_back(Pin{pinNumber, Mode::inputWithInternalPullUp});
        }

        return result;
    }
}