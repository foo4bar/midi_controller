#include "KeyboardMatrixIO.hpp"

namespace kbd
{
    KeyboardMatrixIO KeyboardMatrixIO::Builder::build() const
    {
        return KeyboardMatrixIO(this->firstClosedContactsOutputs,
                                this->lastClosedContactsOutputs,
                                this->inputs,
                                this->numberOfKeysBeingScanned);
    }

    const InputStatePair KeyboardMatrixIO::getActualInstantaneousInputStatePair(const uint8_t contactPairNumber)
    {
        const auto outputNumber{static_cast<uint8_t>(contactPairNumber / this->numberOfInputs)};
        const auto &firstClosedContactsOutput{this->firstClosedContactsOutputs[outputNumber]};
        const auto &lastClosedContactsOutput{this->lastClosedContactsOutputs[outputNumber]};

        const auto inputNumber{static_cast<uint8_t>(contactPairNumber % this->numberOfInputs)};
        const auto &input{this->inputs[inputNumber]};

        return InputStatePair{getInputState(firstClosedContactsOutput, input),
                              getInputState(lastClosedContactsOutput, input)};
    }

    uint8_t KeyboardMatrixIO::getNumberOfKeysBeingScanned() const
    {
        return this->numberOfKeysBeingScanned;
    }

    KeyboardMatrixIO::KeyboardMatrixIO(const std::vector<Pin> &firstClosedContactsOutputs,
                                       const std::vector<Pin> &lastClosedContactsOutputs,
                                       const std::vector<Pin> &inputs,
                                       const uint8_t numberOfKeysBeingScanned) : firstClosedContactsOutputs{firstClosedContactsOutputs},
                                                                                 lastClosedContactsOutputs{lastClosedContactsOutputs},
                                                                                 inputs{inputs},
                                                                                 numberOfInputs{static_cast<uint8_t>(inputs.size())},
                                                                                 numberOfKeysBeingScanned{numberOfKeysBeingScanned}
    {
    }

    State KeyboardMatrixIO::getInputState(const Pin &outputToBounce, const Pin &inputToCheck) const
    {
        outputToBounce.setState(State::low);
        const auto result{inputToCheck.getState()};
        outputToBounce.setState(State::high);

        return result;
    }
}