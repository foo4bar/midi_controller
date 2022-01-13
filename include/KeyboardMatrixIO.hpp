#ifndef KeyboardMatrixIO_hpp
#define KeyboardMatrixIO_hpp

#include <vector>

#include <stdint.h>

#include "DigitalIO.hpp"

namespace kbd
{
    class KeyboardMatrixIO
    {
    private:
        inline static constexpr uint8_t numberOfPins{54};

        //It's supposed that both outputs vectors are of the same size, i.e., numberOfOutputPairs.
        std::vector<uint8_t> firstClosedContactsOutputs;
        std::vector<uint8_t> lastClosedContactsOutputs;
        //It's supposed that the vectors is of size numberOfInputs.
        std::vector<uint8_t> inputs;

        std::vector<arduino::digital::Pin> pins;
        uint8_t numberOfInputs;

        KeyboardMatrixIO(const std::vector<uint8_t> &firstClosedContactsOutputs,
                         const std::vector<uint8_t> &lastClosedContactsOutputs,
                         const std::vector<uint8_t> &inputs) : firstClosedContactsOutputs{firstClosedContactsOutputs},
                                                               lastClosedContactsOutputs{lastClosedContactsOutputs},
                                                               inputs{inputs}
        {
            for (uint8_t pinNumber = 0; pinNumber < numberOfPins; ++pinNumber)
                this->pins.push_back(arduino::digital::Pin{pinNumber});

            for (const auto &outputs : {firstClosedContactsOutputs, lastClosedContactsOutputs})
                for (uint8_t output : outputs)
                {
                    this->pins[output].setMode(arduino::digital::Mode::output);
                    this->pins[output].setState(arduino::digital::State::high);
                }

            for (const uint8_t input : inputs)
                this->pins[input].setMode(arduino::digital::Mode::inputWithInternalPullUp);

            this->numberOfInputs = inputs.size();
        }

        const arduino::digital::State getInputState(const uint8_t outputToToggle, const uint8_t inputToCheck)
        {
            this->pins[outputToToggle].setState(arduino::digital::State::low);
            auto result{this->pins[inputToCheck].getState()};
            this->pins[outputToToggle].setState(arduino::digital::State::high);

            return result;
        }

    public:
        class Builder
        {
        public:
            std::vector<uint8_t> firstClosedContactsOutputs;
            std::vector<uint8_t> lastClosedContactsOutputs;
            std::vector<uint8_t> inputs;

            auto build() const
            {
                return KeyboardMatrixIO{this->firstClosedContactsOutputs,
                                        this->lastClosedContactsOutputs,
                                        this->inputs};
            }
        };

        const arduino::digital::InputStatePair getActualInstantaneousInputStatePair(const uint8_t contactPairNumber)
        {
            const uint8_t outputNumber{(uint8_t)(contactPairNumber / this->numberOfInputs)};
            const uint8_t firstClosedContactsOutput{this->firstClosedContactsOutputs[outputNumber]};
            const uint8_t lastClosedContactsOutput{this->lastClosedContactsOutputs[outputNumber]};

            const uint8_t inputNumber{(uint8_t)(contactPairNumber % this->numberOfInputs)};
            const uint8_t input{this->inputs[inputNumber]};

            return arduino::digital::InputStatePair{getInputState(firstClosedContactsOutput, input),
                                                    getInputState(lastClosedContactsOutput, input)};
        }
    };
}

#endif