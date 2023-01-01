#ifndef KeyboardMatrixIO_hpp
#define KeyboardMatrixIO_hpp

#define NOP __asm__ __volatile__ ("nop\n\t")
#define NOP_2_TIMES NOP; NOP
#define NOP_14_TIMES NOP_2_TIMES; NOP_2_TIMES; NOP_2_TIMES; NOP_2_TIMES; NOP_2_TIMES; NOP_2_TIMES; NOP_2_TIMES

#include <vector>

#include <stdint.h>

#include "DigitalIO.hpp"

namespace kbd
{
    using namespace arduino::digital;

    class KeyboardMatrixIO
    {
    public:
        class Builder
        {
        public:
            const std::vector<Pin> firstActuatedContactsOutputs;
            const std::vector<Pin> lastActuatedContactsOutputs;
            const std::vector<Pin> inputs;
            uint8_t numberOfKeysBeingScanned;

            KeyboardMatrixIO build() const;
        };

        KeyInputStates getActualInstantaneousKeyInputStates(const uint8_t contactPairNumber) const;

        uint8_t getNumberOfKeysBeingScanned() const;

    private:
        inline static constexpr uint8_t numberOfPins{54};

        // It's supposed that both outputs vectors are of the same size.
        const std::vector<Pin> firstActuatedContactsOutputs;
        const std::vector<Pin> lastActuatedContactsOutputs;

        const std::vector<Pin> inputs;

        uint8_t numberOfInputs;
        uint8_t numberOfKeysBeingScanned;

        KeyboardMatrixIO(const std::vector<Pin> &firstActuatedContactsOutputs,
                         const std::vector<Pin> &lastActuatedContactsOutputs,
                         const std::vector<Pin> &inputs,
                         const uint8_t numberOfKeysBeingScanned);

        State getInputState(const Pin &outputToBounce, const Pin &inputToCheck) const;
    };
}

#endif