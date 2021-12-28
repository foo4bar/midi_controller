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
                                                                             inputs{inputs}
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

    const kbd::ContactPairState KeyboardMatrixIO::getActualInstantaneousContactPairState(const uint8_t contactPairNumber) const
    {
        kbd::ContactPairState contactPairState;

        const uint8_t outputNumber{}; //TODO
        const uint8_t inputNumber{};  //TODO

        digital::setPinState(this->firstClosedContactsOutputs[outputNumber], digital::State::low);
        contactPairState.firstClosed = digital::getPinState(this->inputs[inputNumber]) == digital::State::high
                                           ? kbd::Contact::State::open
                                           : kbd::Contact::State::closed;

        digital::setPinState(this->lastClosedContactsOutputs[outputNumber], digital::State::low);
        contactPairState.lastClosed = digital::getPinState(this->inputs[inputNumber]) == digital::State::high
                                          ? kbd::Contact::State::open
                                          : kbd::Contact::State::closed;

        return contactPairState;
    }
}
