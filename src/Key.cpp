#include "Key.hpp"

namespace kbd
{
    Key::Key(const uint8_t number) : number{number},
                                     contacts{ContactPair{number}}
    {
    }

    const bool Key::isSateChanged()
    {
        this->contacts.updateStateWithDebouncing();

        return this->previousState != this->actualState;
    }

    const Key::State &Key::getActualState() const
    {
        return this->actualState;
    }

    const uint8_t Key::getVelocity() const
    {
        return this->velocity;
    }

    const uint8_t Key::getNumber() const
    {
        return this->number;
    }

    void Key::resetStateChange()
    {
        this->previousState = this->actualState;
    }
}