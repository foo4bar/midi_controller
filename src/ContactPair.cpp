#include "ContactPair.hpp"

namespace kbd
{
    ContactPair::ContactPair(const uint8_t number) : number{number}
    {
    }

    void ContactPair::updateStateWithDebouncing(KeyboardMatricesIO *const keyboardMatrices)
    {
        const auto inputStatePair{keyboardMatrices->getActualInstantaneousInputStatePair(this->number)};
        this->firstClosed.updateStateWithDebouncing(inputStatePair.withFirstClosedContactOutput);
        this->lastClosed.updateStateWithDebouncing(inputStatePair.withLastClosedContactOutput);
    }

    const unsigned long ContactPair::getPressingTimeMillis() const
    {
        return this->lastClosed.getLastTimeStateChangedMillis() - this->firstClosed.getLastTimeStateChangedMillis();
    }

    const unsigned long ContactPair::getReleasingTimeMillis() const
    {
        return this->firstClosed.getLastTimeStateChangedMillis() - this->lastClosed.getLastTimeStateChangedMillis();
    }

    const bool ContactPair::isAsKeyIsDepressed() const
    {
        return this->firstClosed.isClosed() && this->lastClosed.isClosed();
    }

    const bool ContactPair::isAsKeyIsReleased() const
    {
        return !this->firstClosed.isClosed() && !this->lastClosed.isClosed();
    }
}