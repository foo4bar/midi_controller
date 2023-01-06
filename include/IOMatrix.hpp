#ifndef IOMatrix_hpp
#define IOMatrix_hpp

#define NOP __asm__ __volatile__("nop\n\t")
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