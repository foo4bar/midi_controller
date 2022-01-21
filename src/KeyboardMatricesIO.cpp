#include "KeyboardMatricesIO.hpp"

namespace kbd
{
    KeyboardMatricesIO::KeyboardMatricesIO(const std::vector<KeyboardMatrixIO> &keyboardMatrices) : keyboardMatrices{keyboardMatrices}
    {
    }

    uint8_t KeyboardMatricesIO::getNumberOfKeysBeingScanned() const
    {
        return std::accumulate(this->keyboardMatrices.begin(),
                               this->keyboardMatrices.end(),
                               0,
                               [](uint8_t init, KeyboardMatrixIO keyboardMatrix)
                               { return init + keyboardMatrix.getNumberOfKeysBeingScanned(); });
    }

    const arduino::digital::InputStatePair KeyboardMatricesIO::getActualInstantaneousInputStatePair(const uint8_t keyNumber)
    {
        uint8_t numberOfKeysBeingScannedByPreviousMatrices{};
        for (auto &keyboardMatrix : this->keyboardMatrices)
        {
            if (keyNumber < (keyboardMatrix.getNumberOfKeysBeingScanned() + numberOfKeysBeingScannedByPreviousMatrices))
            {
                return keyboardMatrix.getActualInstantaneousInputStatePair(keyNumber - numberOfKeysBeingScannedByPreviousMatrices);
            }
            else
            {
                numberOfKeysBeingScannedByPreviousMatrices += keyboardMatrix.getNumberOfKeysBeingScanned();
            }
        }

        return arduino::digital::InputStatePair{};
    }
}