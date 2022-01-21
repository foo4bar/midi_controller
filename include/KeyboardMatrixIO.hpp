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
            std::vector<uint8_t> firstClosedContactsOutputs;
            std::vector<uint8_t> lastClosedContactsOutputs;
            std::vector<uint8_t> inputs;
            uint8_t numberOfKeysBeingScanned;
            std::vector<AvrPin> &avrPins;

            KeyboardMatrixIO build() const;
        };

        const InputStatePair getActualInstantaneousInputStatePair(const uint8_t contactPairNumber);

        uint8_t getNumberOfKeysBeingScanned() const;

    private:
        inline static constexpr uint8_t numberOfPins{54};

        // It's supposed that both outputs vectors are of the same size.
        std::vector<uint8_t> firstClosedContactsOutputs;
        std::vector<uint8_t> lastClosedContactsOutputs;

        std::vector<uint8_t> inputs;

        uint8_t numberOfInputs;
        uint8_t numberOfKeysBeingScanned;
        std::vector<AvrPin> &avrPins;

        KeyboardMatrixIO(const std::vector<uint8_t> &firstClosedContactsOutputs,
                         const std::vector<uint8_t> &lastClosedContactsOutputs,
                         const std::vector<uint8_t> &inputs,
                         const uint8_t numberOfKeysBeingScanned,
                         std::vector<AvrPin> &avrPins);

        State getInputState(AvrPin &outputToBounce, AvrPin &inputToCheck);
    };
}

#endif