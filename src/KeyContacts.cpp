#include "KeyContacts.hpp"

namespace kbd
{
    KeyContacts::KeyContacts(const uint8_t number) : number{number}
    {
    }

    void KeyContacts::updateStateWithDebouncing(const KeyboardMatricesIO &keyboardMatricesIO)
    {
        const auto inputStatePair{keyboardMatricesIO.getActualInstantaneousKeyInputStates(this->number)};
        this->firstActuated.updateStateWithDebouncing(inputStatePair.withFirstActuatedContactOutput);
        this->lastActuated.updateStateWithDebouncing(inputStatePair.withLastActuatedContactOutput);
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