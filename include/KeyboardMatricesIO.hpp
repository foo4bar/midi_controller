#ifndef KeyboardMatrices_hpp
#define KeyboardMatrices_hpp

#include <numeric>

#include <stdint.h>

#include "DigitalIO.hpp"
#include "KeyboardMatrixIO.hpp"

namespace kbd
{
    class KeyboardMatricesIO
    {
    public:
        KeyboardMatricesIO(const std::vector<KeyboardMatrixIO> &keyboardMatrices);

        uint8_t getNumberOfKeysBeingScanned() const;

        arduino::digital::InputStatePair getActualInstantaneousInputStatePair(const uint8_t keyNumber);

    private:
        std::vector<KeyboardMatrixIO> keyboardMatrices;
    };
}

#endif