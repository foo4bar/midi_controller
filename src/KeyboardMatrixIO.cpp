#include "KeyboardMatrixIO.hpp"

namespace kbd
{
    KeyboardMatrixIO KeyboardMatrixIO::Builder::build() const
    {
        return KeyboardMatrixIO(this->outputs,
                                this->inputs);
    }

    KeyInputStates KeyboardMatrixIO::getActualInstantaneousKeyInputStates(const uint8_t keyNumber) const
    {
        const auto outputNumber{static_cast<uint8_t>(keyNumber / this->numberOfInputs)};
        const auto &firstClosedContactOutput{this->outputs[outputNumber].firstActuatedContactOutput};
        const auto &lastClosedContactOutput{this->outputs[outputNumber].lastActuatedContactOutput};

        const auto inputNumber{static_cast<uint8_t>(keyNumber % this->numberOfInputs)};
        const auto &input{this->inputs[inputNumber]};

        return KeyInputStates{getInputState(firstClosedContactOutput, input),
                              getInputState(lastClosedContactOutput, input)};
    }

    uint8_t KeyboardMatrixIO::getNumberOfKeysBeingScanned() const
    {
        return this->numberOfKeysBeingScanned;
    }

    KeyboardMatrixIO::KeyboardMatrixIO(const std::vector<KeyGroupOutputs> &outputs,
                                       const std::vector<Pin> &inputs) : outputs{outputs},
                                                                         inputs{inputs},
                                                                         numberOfInputs{static_cast<uint8_t>(inputs.size())},
                                                                         numberOfKeysBeingScanned{static_cast<uint8_t>(inputs.size() * outputs.size())}
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