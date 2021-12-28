#include "KeyboardController.hpp"

namespace kbd
{
    const std::array<Key, numberOfScannedContactPairs> &KeyboardController::updateKeysStateAndGet()
    {
        for (uint8_t i = 0; i < numberOfScannedContactPairs; i++)
        {
            
        }

        return this->keys;
    }
}