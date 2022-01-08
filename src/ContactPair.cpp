#include "ContactPair.hpp"

namespace kbd
{
    void ContactPair::updateStateWithDebouncing(const uint8_t keyNumber)
    {
        const auto inputStatePair{kbdmatrix::getActualInstantaneousInputStatePair(keyNumber)};
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