#include "KeyContacts.hpp"

namespace kbd
{
    KeyContacts::KeyContacts(const uint8_t number) : number{number}
    {
    }

    void KeyContacts::updateStateWithDebouncing(const IOMatrices &ioMatrices)
    {
        const auto inputStatePair{ioMatrices.getActualInstantaneousKeyInputStates(this->number)};
        this->firstActuated.updateStateWithDebouncing(inputStatePair.withFirstActuatedKeyContactOutput);
        this->lastActuated.updateStateWithDebouncing(inputStatePair.withLastActuatedKeyContactOutput);
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