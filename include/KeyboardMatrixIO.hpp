#ifndef KeyboardMatrixIO_hpp
#define KeyboardMatrixIO_hpp

#include <array>

#include <stdint.h>

#include "DigitalIO.hpp"

namespace kbdmatrix
{
    template <uint8_t numberOfOutputPairs, uint8_t numberOfInputs>
    class KeyboardMatrixIO
    {
    private:
        inline static constexpr uint8_t numberOfPins{54};

        std::array<arduino::digital::Pin, numberOfPins> pins;

        //It's supposed that both outputs vectors are of the same size, i.e., numberOfOutputPairs. This is enforced by KeyboardMatrixIO::Builder.
        std::array<uint8_t, numberOfOutputPairs> firstClosedContactsOutputs;
        std::array<uint8_t, numberOfOutputPairs> lastClosedContactsOutputs;
        //It's supposed that the vectors is of size numberOfInputs. This is enforced by KeyboardMatrixIO::Builder.
        std::array<uint8_t, numberOfInputs> inputs;

        KeyboardMatrixIO(const std::array<uint8_t, numberOfOutputPairs> &firstClosedContactsOutputs,
                         const std::array<uint8_t, numberOfOutputPairs> &lastClosedContactsOutputs,
                         const std::array<uint8_t, numberOfInputs> &inputs) : firstClosedContactsOutputs{firstClosedContactsOutputs},
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

        const arduino::digital::State getInputState(const uint8_t outputToToggle, const uint8_t inputToCheck)
        {
            this->pins[outputToToggle].setState(arduino::digital::State::low);
            auto result{this->pins[inputToCheck].getState()};
            this->pins[outputToToggle].setState(arduino::digital::State::high);

            return result;
        }

    public:
        template <uint8_t numberOfOutputPairsBuilder, uint8_t numberOfInputsBuilder>
        class Builder
        {
        private:
            std::array<uint8_t, numberOfOutputPairsBuilder> firstClosedContactsOutputs;
            std::array<uint8_t, numberOfOutputPairsBuilder> lastClosedContactsOutputs;
            std::array<uint8_t, numberOfInputsBuilder> inputs;

        public:
            Builder &withFirstClosedContactsOutputs(const std::array<uint8_t, numberOfOutputPairsBuilder> &outputs)
            {
                this->firstClosedContactsOutputs = outputs;
                return *this;
            }

            Builder &withLastClosedContactsOutputs(const std::array<uint8_t, numberOfOutputPairsBuilder> &outputs)
            {
                this->lastClosedContactsOutputs = outputs;
                return *this;
            }

            Builder &withInputs(const std::array<uint8_t, numberOfInputsBuilder> &inputs)
            {
                this->inputs = inputs;
                return *this;
            }

            KeyboardMatrixIO<numberOfOutputPairsBuilder, numberOfInputsBuilder> build() const
            {
                return KeyboardMatrixIO<numberOfOutputPairsBuilder, numberOfInputsBuilder>{this->firstClosedContactsOutputs,
                                                                                           this->lastClosedContactsOutputs,
                                                                                           this->inputs};
            }
        };

        const arduino::digital::InputStatePair getActualInstantaneousInputStatePair(const uint8_t contactPairNumber)
        {
            const uint8_t outputNumber{(uint8_t)(contactPairNumber / numberOfInputs)};
            const uint8_t firstClosedContactsOutput{this->firstClosedContactsOutputs[outputNumber]};
            const uint8_t lastClosedContactsOutput{this->lastClosedContactsOutputs[outputNumber]};

            const uint8_t inputNumber{(uint8_t)(contactPairNumber % numberOfInputs)};
            const uint8_t input{this->inputs[inputNumber]};

            return arduino::digital::InputStatePair{getInputState(firstClosedContactsOutput, input),
                                                    getInputState(lastClosedContactsOutput, input)};
        }
    };
}

#endif