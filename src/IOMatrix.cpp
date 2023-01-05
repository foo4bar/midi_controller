#include "IOMatrix.hpp"

namespace arduino::digital
{
    IOMatrix IOMatrix::Builder::build() const
    {
        return IOMatrix(this->keyGroupsOutputs,
                        this->keysInputs);
    }

    KeyInputStates IOMatrix::getActualInstantaneousKeyInputStates(const uint8_t keyNumber) const
    {
        const auto outputNumber{static_cast<uint8_t>(keyNumber / this->numberOfInputs)};
        const auto &firstClosedKeyContactOutput{this->keyGroupsOutputs[outputNumber].firstActuatedKeysContactsOutput};
        const auto &lastClosedKeyContactOutput{this->keyGroupsOutputs[outputNumber].lastActuatedKeysContactsOutput};

        const auto inputNumber{static_cast<uint8_t>(keyNumber % this->numberOfInputs)};
        const auto &input{this->keysInputs[inputNumber]};

        return KeyInputStates{getInputState(firstClosedKeyContactOutput, input),
                              getInputState(lastClosedKeyContactOutput, input)};
    }

    uint8_t IOMatrix::getNumberOfKeysBeingScanned() const
    {
        return this->numberOfKeysBeingScanned;
    }

    IOMatrix::IOMatrix(const std::vector<KeyGroupOutputs> &keyGroupsOutputs,
                       const std::vector<Pin> &keysInputs) : keyGroupsOutputs{keyGroupsOutputs},
                                                             keysInputs{keysInputs},
                                                             numberOfInputs{static_cast<uint8_t>(keysInputs.size())},
                                                             numberOfKeysBeingScanned{static_cast<uint8_t>(keysInputs.size() * keyGroupsOutputs.size())}
    {
    }

    State IOMatrix::getInputState(const Pin &outputToBounce, const Pin &inputToCheck) const
    {
        outputToBounce.setState(State::low);
        NOP_14_TIMES;

        const auto result{inputToCheck.getState()};

        outputToBounce.setState(State::high);
        NOP_14_TIMES;

        return result;
    }
}