#include "KeyboardController.hpp"

namespace kbd
{
    const std::vector<Key> &KeyboardController::getKeys() const
    {
        
        return this->keys;
    }
}