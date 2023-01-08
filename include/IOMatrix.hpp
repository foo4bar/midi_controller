#ifndef IOMatrix_hpp
#define IOMatrix_hpp

#define NOP __asm__ __volatile__("nop\n\t")

// After IO matrix outputs state changes, it's needed to wait till voltage on IO matrix inputs is more or less steady,
// i.e., transitional process oscillation magnitude is small enough to not affect inputs state reading correctness.
// The waiting time depends on schematics and is to be determined empirically.
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
        IOMatrix(const std::vector<KeyGroupOutputs> &keyGroupsOutputs,
                 const std::vector<Pin> &keysInputs);

        std::vector<KeyInputStates> getActualInstantaneousKeysInputsStates() const;

        uint8_t getNumberOfKeysBeingScanned() const;

    private:
        const std::vector<KeyGroupOutputs> keyGroupsOutputs;
        const std::vector<Pin> keysInputs;

        uint8_t numberOfInputs;
        uint8_t numberOfKeysBeingScanned;
    };
}

#endif