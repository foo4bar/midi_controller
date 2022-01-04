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
        InputStatePair statePair;

        const uint8_t outputNumber{}; //TODO
        const uint8_t inputNumber{};  //TODO

        setPinState(this->firstClosedContactsOutputs[outputNumber], State::low); //TODO extract to getInputSate()
        statePair.withFirstClosedContactOutput = getPinState(this->inputs[inputNumber]);
        setPinState(this->firstClosedContactsOutputs[outputNumber], State::high);

        setPinState(this->lastClosedContactsOutputs[outputNumber], State::low);
        statePair.withLastClosedContactOutput = getPinState(this->inputs[inputNumber]);
        setPinState(this->lastClosedContactsOutputs[outputNumber], State::high);

        return statePair;
    }
}