#include "KeyboardMatrixIO.hpp"

namespace kbdmatrix
{
    KeyboardMatrixIO::KeyboardMatrixIO(const uint8_t numberOfOutputPairs,
                                       const uint8_t numberOfInputs,
                                       const std::vector<Pin> &firstClosedContactsOutputs,
                                       const std::vector<Pin> &lastClosedContactsOutputs,
                                       const std::vector<uint8_t> &inputs) : numberOfOutputPairs{numberOfOutputPairs},
                                                                             numberOfInputs{numberOfInputs},
                                                                             firstClosedContactsOutputs{firstClosedContactsOutputs},
                                                                             lastClosedContactsOutputs{lastClosedContactsOutputs},
                                                                             inputs{inputs}
    {
        for (const auto &outputs : {firstClosedContactsOutputs, lastClosedContactsOutputs})
            for (Pin output : outputs)
            {
                setPinMode(output.getNumber(), Mode::output);
                output.setHigh();
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

    const State KeyboardMatrixIO::getInputState(std::vector<Pin> outputs,
                                                const uint8_t outputNumber,
                                                const uint8_t inputNumber) const
    {
        outputs[outputNumber].setLow();
        State result{getPinState(this->inputs[inputNumber])};
        outputs[outputNumber].setHigh();

        return result;
    }
}