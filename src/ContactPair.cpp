#include "ContactPair.hpp"

namespace kbd
{
    ContactPair::ContactPair(const uint8_t number) : number{number}
    {
    }

    void ContactPair::updateStateWithDebouncing(KeyboardMatricesIO &keyboardMatrices)
    {
        const auto inputStatePair{keyboardMatrices.getActualInstantaneousInputStatePair(this->number)};
        this->firstClosed.updateStateWithDebouncing(inputStatePair.withFirstClosedContactOutput);
        this->lastClosed.updateStateWithDebouncing(inputStatePair.withLastClosedContactOutput);
    }

    unsigned long ContactPair::getPressingTimeMillis() const
    {
        return this->lastClosed.getLastTimeStateChangedMillis() - this->firstClosed.getLastTimeStateChangedMillis();
    }

    bool ContactPair::isAsKeyIsDepressed() const
    {
        return this->firstClosed.isClosed() && this->lastClosed.isClosed();
    }

    bool ContactPair::isAsKeyIsReleased() const
    {
        return !this->firstClosed.isClosed() && !this->lastClosed.isClosed();
    }
}