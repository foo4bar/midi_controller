#include "DigitalIO.hpp"
#include "KeyboardMatrixIO.hpp"

namespace arduino::digital
{
    KeyboardMatrixIO::KeyboardMatrixIO(const uint8_t numberOfOutputPairs,
                                       const uint8_t numberOfInputs,
                                       const std::vector<uint8_t> &firstClosedContactsOutputs,
                                       const std::vector<uint8_t> &lastClosedContactsOutputs,
                                       const std::vector<uint8_t> &inputs) : numberOfOutputPairs{numberOfOutputPairs},
                                                                             numberOfInputs{numberOfInputs},
                                                                             firstClosedContactsOutputs{firstClosedContactsOutputs},
                                                                             lastClosedContactsOutputs{lastClosedContactsOutputs},
                                                                             inputs{inputs},
                                                                             contacts{std::vector<std::vector<kbd::Contact>>(numberOfOutputPairs, std::vector<kbd::Contact>(numberOfInputs))}
    {
        for (const auto &outputs : {firstClosedContactsOutputs, lastClosedContactsOutputs})
            for (const uint8_t output : outputs)
            {
                digital::setPinMode(output, digital::Mode::output);
                digital::setPinState(output, digital::State::high);
            }

        for (const uint8_t input : inputs)
            digital::setPinMode(input, digital::Mode::inputWithInternalPullUp);
    }

    const void KeyboardMatrixIO::updateContactsState(std::vector<std::vector<kbd::Contact>> &contacts) const
    {
        for (const auto &outputs : {this->firstClosedContactsOutputs, this->lastClosedContactsOutputs})
            for (uint8_t i = 0; i < this->numberOfOutputPairs; i++)
            {
                digital::setPinState(outputs[i], digital::State::low);

                for (uint8_t j = 0; j < this->numberOfInputs; j++)
                {
                    const auto actualInstantaneousState{digital::getPinState(this->inputs[j]) == digital::State::high
                                                            ? kbd::Contact::State::open
                                                            : kbd::Contact::State::closed};
                    contacts[i][j].updateStateWithDebouncing(actualInstantaneousState);
                }

                digital::setPinState(outputs[i], digital::State::high);
            }
    }

    uint8_t KeyboardMatrixIO::getNumberOfKeys() const
    {
        return this->numberOfOutputPairs * this->numberOfInputs;
    }
}
