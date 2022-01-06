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
        for (const auto &outputs : {firstClosedContactsOutputs, lastClosedContactsOutputs})
            for (const uint8_t output : outputs)
            {
                setPinMode(output, Mode::output);
                setPinState(output, State::high);
            }

        for (const uint8_t input : inputs)
            setPinMode(input, Mode::inputWithInternalPullUp);
    }

    const InputStatePair KeyboardMatrixIO::getActualInstantaneousInputStatePair(const uint8_t contactPairNumber) const
    {
        const uint8_t outputNumber{(uint8_t)(contactPairNumber / numberOfInputs)};
        const uint8_t inputNumber{(uint8_t)(contactPairNumber % this->numberOfInputs)};

        return InputStatePair{getInputState(this->firstClosedContactsOutputs, outputNumber, inputNumber),
                              getInputState(this->lastClosedContactsOutputs, outputNumber, inputNumber)};
    }

    const State KeyboardMatrixIO::getInputState(const std::vector<uint8_t> outputs,
                                                const uint8_t outputNumber,
                                                const uint8_t inputNumber) const
    {
        setPinState(outputs[outputNumber], State::low);
        State result{getPinState(this->inputs[inputNumber])};
        setPinState(outputs[outputNumber], State::high);

        return result;
    }
}