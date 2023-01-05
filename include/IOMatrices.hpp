#ifndef IOMatrices_hpp
#define IOMatrices_hpp

#include <numeric>
#include <vector>

#include <stdint.h>

#include "DigitalIO.hpp"
#include "IOMatrix.hpp"

namespace kbd
{
    class IOMatrices
    {
    public:
        explicit IOMatrices(const std::vector<IOMatrix> &);

        uint8_t getNumberOfKeysBeingScanned() const;

        arduino::digital::KeyInputStates getActualInstantaneousKeyInputStates(const uint8_t keyNumber) const;

    private:
        std::vector<IOMatrix> ioMatrices;
        uint8_t numberOfKeysBeingScanned;
    };
}

#endif