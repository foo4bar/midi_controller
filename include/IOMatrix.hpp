#ifndef IOMatrix_hpp
#define IOMatrix_hpp

#define NOP __asm__ __volatile__("nop\n\t")
#define NOP_2_TIMES \
    NOP;            \
    NOP
#define NOP_14_TIMES \
    NOP_2_TIMES;     \
    NOP_2_TIMES;     \
    NOP_2_TIMES;     \
    NOP_2_TIMES;     \
    NOP_2_TIMES;     \
    NOP_2_TIMES;     \
    NOP_2_TIMES

#include <vector>

#include <stdint.h>

#include "DigitalIO.hpp"

namespace arduino::digital
{
    class IOMatrix
    {
    public:
        class Builder
        {
        public:
            const std::vector<KeyGroupOutputs> keyGroupsOutputs;
            const std::vector<Pin> keysInputs;

            IOMatrix build() const;
        };

        KeyInputStates getActualInstantaneousKeyInputStates(const uint8_t contactPairNumber) const;

        uint8_t getNumberOfKeysBeingScanned() const;

    private:
        const std::vector<KeyGroupOutputs> keyGroupsOutputs;
        const std::vector<Pin> keysInputs;

        uint8_t numberOfInputs;
        uint8_t numberOfKeysBeingScanned;

        IOMatrix(const std::vector<KeyGroupOutputs> &keyGroupsOutputs,
                 const std::vector<Pin> &keysInputs);

        State getInputState(const Pin &outputToBounce, const Pin &inputToCheck) const;
    };
}

#endif