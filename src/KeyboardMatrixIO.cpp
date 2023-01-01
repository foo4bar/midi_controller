#include "KeyboardMatrixIO.hpp"

namespace kbd
{
    KeyboardMatrixIO KeyboardMatrixIO::Builder::build() const
    {
        return KeyboardMatrixIO(this->firstActuatedContactsOutputs,
                                this->lastActuatedContactsOutputs,
                                this->inputs,
                                this->numberOfKeysBeingScanned);
    }

    KeyInputStates KeyboardMatrixIO::getActualInstantaneousKeyInputStates(const uint8_t contactPairNumber) const
    {
        const auto outputNumber{static_cast<uint8_t>(contactPairNumber / this->numberOfInputs)};
        const auto &firstClosedContactOutput{this->firstActuatedContactsOutputs[outputNumber]};
        const auto &lastClosedContactOutput{this->lastActuatedContactsOutputs[outputNumber]};

        const auto inputNumber{static_cast<uint8_t>(contactPairNumber % this->numberOfInputs)};
        const auto &input{this->inputs[inputNumber]};

        return KeyInputStates{getInputState(firstClosedContactOutput, input),
                              getInputState(lastClosedContactOutput, input)};
    }

    uint8_t KeyboardMatrixIO::getNumberOfKeysBeingScanned() const
    {
        return this->numberOfKeysBeingScanned;
    }

    KeyboardMatrixIO::KeyboardMatrixIO(const std::vector<Pin> &firstActuatedContactsOutputs,
                                       const std::vector<Pin> &lastActuatedContactsOutputs,
                                       const std::vector<Pin> &inputs,
                                       const uint8_t numberOfKeysBeingScanned) : firstActuatedContactsOutputs{firstActuatedContactsOutputs},
                                                                                 lastActuatedContactsOutputs{lastActuatedContactsOutputs},
                                                                                 inputs{inputs},
                                                                                 numberOfInputs{static_cast<uint8_t>(inputs.size())},
                                                                                 numberOfKeysBeingScanned{numberOfKeysBeingScanned}
    {
    }

    State KeyboardMatrixIO::getInputState(const Pin &outputToBounce, const Pin &inputToCheck) const
    {
        outputToBounce.setState(State::low);
        NOP_14_TIMES;

        const auto result{inputToCheck.getState()};

        outputToBounce.setState(State::high);
        NOP_14_TIMES;

        return result;
    }
}