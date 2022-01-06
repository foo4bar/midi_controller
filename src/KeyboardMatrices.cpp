#include "KeyboardMatrices.hpp"

namespace kbdmatrix
{
    const arduino::digital::InputStatePair getActualInstantaneousInputStatePair(const uint8_t keyNumber)
    {
        if (keyNumber < numberOfScannedKeys)
        {
            if (keyNumber < numberOfScannedKeysLeft)
            {
                return keyboardMatrixIOLeft.getActualInstantaneousInputStatePair(keyNumber);
            }
            else
            {
                return keyboardMatrixIORight.getActualInstantaneousInputStatePair(keyNumber - numberOfScannedKeysLeft);
            }
        }
        else
        {
            return arduino::digital::InputStatePair{};
        }
    }
}