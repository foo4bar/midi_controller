#include "KeyboardMatricesIO.hpp"

namespace kbd
{
    KeyboardMatricesIO::KeyboardMatricesIO(const std::vector<KeyboardMatrixIO> &keyboardMatricesIO) : keyboardMatricesIO{keyboardMatricesIO}
    {
    }

    uint8_t KeyboardMatricesIO::getNumberOfKeysBeingScanned() const
    {
        return std::accumulate(this->keyboardMatricesIO.begin(),
                               this->keyboardMatricesIO.end(),
                               0,
                               [](uint8_t init, const KeyboardMatrixIO &keyboardMatrixIO)
                               { return init + keyboardMatrixIO.getNumberOfKeysBeingScanned(); });
    }

    arduino::digital::KeyInputStates KeyboardMatricesIO::getActualInstantaneousKeyInputStates(const uint8_t keyNumber) const
    {
        uint8_t numberOfKeysBeingScannedByPreviousMatrices{};
        for (const auto &keyboardMatrixIO : this->keyboardMatricesIO)
        {
            if (keyNumber < (keyboardMatrixIO.getNumberOfKeysBeingScanned() + numberOfKeysBeingScannedByPreviousMatrices))
            {
                return keyboardMatrixIO.getActualInstantaneousKeyInputStates(keyNumber - numberOfKeysBeingScannedByPreviousMatrices);
            }
            else
            {
                numberOfKeysBeingScannedByPreviousMatrices += keyboardMatrixIO.getNumberOfKeysBeingScanned();
            }
        }

        return arduino::digital::KeyInputStates{};
    }
}