#include "KeyboardController.hpp"

namespace kbd
{
    const std::array<Key, arduino::digital::numberOfServedContactPairs> &KeyboardController::getKeys() const
    {
        return this->keys;
    }
}