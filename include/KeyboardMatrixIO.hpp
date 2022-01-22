#ifndef KeyboardMatrixIO_hpp
#define KeyboardMatrixIO_hpp

#include <vector>
#include <memory>

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
            const std::vector<Pin> firstClosedContactsOutputs;
            const std::vector<Pin> lastClosedContactsOutputs;
            const std::vector<Pin> inputs;
            uint8_t numberOfKeysBeingScanned;

            KeyboardMatrixIO build() const;
        };

        const InputStatePair getActualInstantaneousInputStatePair(const uint8_t contactPairNumber);

        uint8_t getNumberOfKeysBeingScanned() const;

    private:
        inline static constexpr uint8_t numberOfPins{54};

        // It's supposed that both outputs vectors are of the same size.
        const std::vector<Pin> firstClosedContactsOutputs;
        const std::vector<Pin> lastClosedContactsOutputs;

        const std::vector<Pin> inputs;

        uint8_t numberOfInputs;
        uint8_t numberOfKeysBeingScanned;

        KeyboardMatrixIO(const std::vector<Pin> &firstClosedContactsOutputs,
                         const std::vector<Pin> &lastClosedContactsOutputs,
                         const std::vector<Pin> inputs,
                         const uint8_t numberOfKeysBeingScanned);

        State getInputState(const Pin &outputToBounce, const Pin &inputToCheck) const;
    };
}

#endif