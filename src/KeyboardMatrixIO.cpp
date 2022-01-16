#include "KeyboardMatrixIO.hpp"

namespace kbd
{
    KeyboardMatrixIO KeyboardMatrixIO::Builder::build() const
    {
        return KeyboardMatrixIO(this->firstClosedContactsOutputs,
                                this->lastClosedContactsOutputs,
                                this->inputs,
                                this->numberOfKeysBeingScanned,
                                this->avrPins);
    }

    const InputStatePair KeyboardMatrixIO::getActualInstantaneousInputStatePair(const uint8_t contactPairNumber)
    {
        const uint8_t outputNumber{static_cast<uint8_t>(contactPairNumber / this->numberOfInputs)};
        const uint8_t firstClosedContactsOutput{this->firstClosedContactsOutputs[outputNumber]};
        const uint8_t lastClosedContactsOutput{this->lastClosedContactsOutputs[outputNumber]};

        const uint8_t inputNumber{static_cast<uint8_t>(contactPairNumber % this->numberOfInputs)};
        const uint8_t input{this->inputs[inputNumber]};

        return InputStatePair{getInputState(firstClosedContactsOutput, input),
                              getInputState(lastClosedContactsOutput, input)};
    }

    uint8_t KeyboardMatrixIO::getNumberOfKeysBeingScanned() const
    {
        return this->numberOfKeysBeingScanned;
    }

    KeyboardMatrixIO::KeyboardMatrixIO(const std::vector<uint8_t> &firstClosedContactsOutputs,
                                       const std::vector<uint8_t> &lastClosedContactsOutputs,
                                       const std::vector<uint8_t> &inputs,
                                       const uint8_t numberOfKeysBeingScanned,
                                       std::vector<AvrPin> &avrPins) : firstClosedContactsOutputs{firstClosedContactsOutputs},
                                                                       lastClosedContactsOutputs{lastClosedContactsOutputs},
                                                                       inputs{inputs},
                                                                       numberOfKeysBeingScanned{numberOfKeysBeingScanned},
                                                                       avrPins{avrPins}
    {
        for (const auto &outputs : {firstClosedContactsOutputs, lastClosedContactsOutputs})
            for (uint8_t output : outputs)
            {
                this->avrPins[output].setMode(Mode::output);
                this->avrPins[output].setState(State::high);
            }

        for (const uint8_t input : inputs)
            this->avrPins[input].setMode(Mode::inputWithInternalPullUp);

        this->numberOfInputs = inputs.size();
    }

    State KeyboardMatrixIO::getInputState(const uint8_t outputToBounce, const uint8_t inputToCheck)
    {
        this->avrPins[outputToBounce].setState(State::low);
        auto result{this->avrPins[inputToCheck].getState()};
        this->avrPins[outputToBounce].setState(State::high);

        return result;
    }
}