#include "KeyboardMatrixIO.hpp"

namespace kbd
{
    KeyboardMatrixIO KeyboardMatrixIO::Builder::build() const
    {
        return KeyboardMatrixIO(this->firstClosedContactsOutputs,
                                this->lastClosedContactsOutputs,
                                this->inputs,
                                this->numberOfKeysBeingScanned,
                                this->pins);
    }

    const InputStatePair KeyboardMatrixIO::getActualInstantaneousInputStatePair(const uint8_t contactPairNumber)
    {
        const auto outputNumber{static_cast<uint8_t>(contactPairNumber / this->numberOfInputs)};
        const auto &firstClosedContactsOutput{this->pins[this->firstClosedContactsOutputs[outputNumber]]};
        const auto &lastClosedContactsOutput{this->pins[this->lastClosedContactsOutputs[outputNumber]]};

        const auto inputNumber{static_cast<uint8_t>(contactPairNumber % this->numberOfInputs)};
        const auto &input{this->pins[this->inputs[inputNumber]]};

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
                                       std::vector<Pin> &pins) : firstClosedContactsOutputs{firstClosedContactsOutputs},
                                                                 lastClosedContactsOutputs{lastClosedContactsOutputs},
                                                                 inputs{inputs},
                                                                 numberOfKeysBeingScanned{numberOfKeysBeingScanned},
                                                                 pins{pins}
    {
        for (const auto &outputs : {firstClosedContactsOutputs, lastClosedContactsOutputs})
            for (const uint8_t output : outputs)
            {
                this->pins[output].setMode(Mode::output);
                this->pins[output].setState(State::high);
            }

        for (const uint8_t input : inputs)
            this->pins[input].setMode(Mode::inputWithInternalPullUp);

        this->numberOfInputs = inputs.size();
    }

    State KeyboardMatrixIO::getInputState(const Pin &outputToBounce, const Pin &inputToCheck) const
    {
        outputToBounce.setState(State::low);
        const auto result{inputToCheck.getState()};
        outputToBounce.setState(State::high);

        return result;
    }
}