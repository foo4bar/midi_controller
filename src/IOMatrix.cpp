#include "IOMatrix.hpp"

namespace arduino::digital
{
    IOMatrix IOMatrix::Builder::build() const
    {
        return IOMatrix(this->keyGroupsOutputs,
                        this->keysInputs);
    }

    std::vector<KeyInputStates> IOMatrix::getActualInstantaneousKeysInputsStates() const
    {
        std::vector<KeyInputStates> keysInputsStates{};

        for (const auto &keyGroupOutputs : this->keyGroupsOutputs)
        {
            keyGroupOutputs.firstActuatedKeysContactsOutput.setState(State::low);
            WAIT_FOR_STEADY_STATE;

            std::vector<State> inputsStatesWithFirstActuatedKeysContactsOutput{};
            for (const auto &keyInput : this->keysInputs)
            {
                inputsStatesWithFirstActuatedKeysContactsOutput.push_back(keyInput.getState());
            }

            keyGroupOutputs.firstActuatedKeysContactsOutput.setState(State::high);
            WAIT_FOR_STEADY_STATE;
            keyGroupOutputs.lastActuatedKeysContactsOutput.setState(State::low);
            WAIT_FOR_STEADY_STATE;

            std::vector<State> inputsStatesWithLastActuatedKeysContactsOutput{};
            for (const auto &keyInput : this->keysInputs)
            {
                inputsStatesWithLastActuatedKeysContactsOutput.push_back(keyInput.getState());
            }

            keyGroupOutputs.lastActuatedKeysContactsOutput.setState(State::high);
            WAIT_FOR_STEADY_STATE;

            for (uint8_t keyInputNumber{0}; keyInputNumber < this->numberOfInputs; ++keyInputNumber)
            {
                keysInputsStates.push_back({inputsStatesWithFirstActuatedKeysContactsOutput[keyInputNumber],
                                            inputsStatesWithLastActuatedKeysContactsOutput[keyInputNumber]});
            }
        }

        return keysInputsStates;
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
}