#ifndef IOMatrices_hpp
#define IOMatrices_hpp

#include <numeric>
#include <vector>

#include <stdint.h>

#include "DigitalIO.hpp"
#include "IOMatrix.hpp"

namespace arduino::digital
{
    class IOMatrices
    {
    public:
        explicit IOMatrices(const std::vector<IOMatrix> &);

        uint8_t getNumberOfKeysBeingScanned() const;

        std::vector<KeyInputStates> getActualInstantaneousKeysInputStates() const;

    private:
        std::vector<IOMatrix> ioMatrices;
        uint8_t numberOfKeysBeingScanned;

        KeyInputStates getActualInstantaneousKeyInputStates(const uint8_t keyNumber) const;
    };
}

#endif