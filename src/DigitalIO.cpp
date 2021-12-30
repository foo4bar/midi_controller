// Arduino.h is to be included right here, not in the header.
#include <Arduino.h>

#include "DigitalIO.hpp"

namespace arduino::digital
{
    void setPinMode(const uint8_t pinNumber, const Mode mode)
    {
        pinMode(pinNumber, static_cast<uint8_t>(mode));
    }

    const State getPinState(const uint8_t pinNumber)
    {
        return static_cast<State>(digitalRead(pinNumber));
    }

    void setPinState(const uint8_t pinNumber, const State state)
    {
        digitalWrite(pinNumber, static_cast<uint8_t>(state));
    }

    const StatePair getActualInstantaneousInputStatePair(const uint8_t contactPairNumber)
    {
        //TODO

        return StatePair{};
    }

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
                setPinMode(output, Mode::output);
                setPinState(output, State::high);
            }

        for (const uint8_t input : inputs)
            setPinMode(input, Mode::inputWithInternalPullUp);
    }

    const StatePair KeyboardMatrixIO::getActualInstantaneousInputStatePair(const uint8_t contactPairNumber) const
    {
        StatePair statePair;

        const uint8_t outputNumber{}; //TODO
        const uint8_t inputNumber{};  //TODO

        setPinState(this->firstClosedContactsOutputs[outputNumber], State::low);
        statePair.firstClosed = getPinState(this->inputs[inputNumber]);
        setPinState(this->firstClosedContactsOutputs[outputNumber], State::high);

        setPinState(this->lastClosedContactsOutputs[outputNumber], State::low);
        statePair.lastClosed = getPinState(this->inputs[inputNumber]);
        setPinState(this->lastClosedContactsOutputs[outputNumber], State::high);

        return statePair;
    }
}