#ifndef IOMatrix_hpp
#define IOMatrix_hpp

#define NOP __asm__ __volatile__("nop\n\t")

// The waiting time depends on schematics and is to be determined empirically.
// It's needed to wait till voltage on IO matrix inputs is more or less steady,
// i.e., transitional process oscillation magnitude, after corresponding
// outputs state changes, doesn't affect inputs state reading correctness.
#define WAIT_FOR_STEADY_STATE \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP;                      \
    NOP

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

        std::vector<KeyInputStates> getActualInstantaneousKeysInputsStates() const;

        uint8_t getNumberOfKeysBeingScanned() const;

    private:
        const std::vector<KeyGroupOutputs> keyGroupsOutputs;
        const std::vector<Pin> keysInputs;

        uint8_t numberOfInputs;
        uint8_t numberOfKeysBeingScanned;

        IOMatrix(const std::vector<KeyGroupOutputs> &keyGroupsOutputs,
                 const std::vector<Pin> &keysInputs);
    };
}

#endif