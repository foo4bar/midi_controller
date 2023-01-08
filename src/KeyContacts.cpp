#include "KeyContacts.hpp"

namespace kbd
{
    void KeyContacts::updateStateWithDebouncing(const arduino::digital::KeyInputStates &keyInputStates)
    {
        this->firstActuated.updateStateWithDebouncing(keyInputStates.withFirstActuatedKeyContactOutput);
        this->lastActuated.updateStateWithDebouncing(keyInputStates.withLastActuatedKeyContactOutput);
    }

    unsigned long KeyContacts::getKeyPressingTimeMillis() const
    {
        return this->lastActuated.getLastTimeStateChangedMillis() - this->firstActuated.getLastTimeStateChangedMillis();
    }

    bool KeyContacts::isAsKeyIsDepressed() const
    {
        return !this->firstActuated.isClosed() && this->lastActuated.isClosed();
    }

    bool KeyContacts::isAsKeyIsReleased() const
    {
        return this->firstActuated.isClosed() && !this->lastActuated.isClosed();
    }
}
