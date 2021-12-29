#include "Key.hpp"

namespace kbd
{
    const bool Key::isSateChanged()
    {
        //TODO Calculate actual state based on contacts state.

        return this->previousState != this->actualState;
    }

    const Key::State &Key::getActualState() const
    {
        return this->actualState;
    }

    void Key::resetStateChange()
    {
        this->previousState = this->actualState;
    }
}