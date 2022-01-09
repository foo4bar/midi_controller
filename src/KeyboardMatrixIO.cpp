#include "KeyboardMatrixIO.hpp"

namespace kbdmatrix
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
        std::array<arduino::digital::Pin, numberOfPins> pins;
        for (uint8_t pinNumber = 0; pinNumber < numberOfPins; ++pinNumber)
            pins[pinNumber] = arduino::digital::Pin{pinNumber};

        for (const auto &outputs : {firstClosedContactsOutputs, lastClosedContactsOutputs})
            for (uint8_t outputToToggle : outputs)
            {
                pins[outputToToggle].setMode(arduino::digital::Mode::output);
                pins[outputToToggle].setState(arduino::digital::State::high);
            }

        for (const uint8_t input : inputs)
            pins[input].setMode(arduino::digital::Mode::inputWithInternalPullUp);

        this->pins = pins;
    }

    const arduino::digital::InputStatePair KeyboardMatrixIO::getActualInstantaneousInputStatePair(const uint8_t contactPairNumber)
    {
        const uint8_t outputNumber{(uint8_t)(contactPairNumber / numberOfInputs)};
        const uint8_t firstClosedContactsOutput{this->firstClosedContactsOutputs[outputNumber]};
        const uint8_t lastClosedContactsOutput{this->lastClosedContactsOutputs[outputNumber]};

        const uint8_t inputNumber{(uint8_t)(contactPairNumber % this->numberOfInputs)};
        const uint8_t input{this->inputs[inputNumber]};

        return arduino::digital::InputStatePair{getInputState(firstClosedContactsOutput, input),
                                                getInputState(lastClosedContactsOutput, input)};
    }

    const arduino::digital::State KeyboardMatrixIO::getInputState(const uint8_t outputToToggle, const uint8_t inputToCheck)
    {
        this->pins[outputToToggle].setState(arduino::digital::State::low);
        auto result{this->pins[inputToCheck].getState()};
        this->pins[outputToToggle].setState(arduino::digital::State::high);

        return result;
    }
}