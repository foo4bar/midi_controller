#include "ContactPair.hpp"

namespace kbd
{
    void ContactPair::updateStateWithDebouncing(const uint8_t number)
    {
        const auto inputStatePair{kbdmatrix::getActualInstantaneousInputStatePair(number)};
        this->firstClosed.updateStateWithDebouncing(inputStatePair.withFirstClosedContactOutput);
        this->lastClosed.updateStateWithDebouncing(inputStatePair.withLastClosedContactOutput);
    }

    const unsigned long ContactPair::getPressingTimeMillis() const
    {
        return this->firstClosed.getLastTimeStateChangedMillis() - this->lastClosed.getLastTimeStateChangedMillis();
    }

    const unsigned long ContactPair::getReleasingTimeMillis() const
    {
        return this->lastClosed.getLastTimeStateChangedMillis() - this->firstClosed.getLastTimeStateChangedMillis();
    }

    const bool ContactPair::isAsKeyIsDepressed() const
    {
        return this->firstClosed.isClosed() && this->lastClosed.isClosed();
    }

    const bool ContactPair::isAsKeyIsReleased() const
    {
        return !this->firstClosed.isClosed() && !this->lastClosed.isClosed();
    }

    const bool ContactPair::isAsKeyIsHalfReleased() const
    {
        return this->firstClosed.isClosed() && !this->lastClosed.isClosed();
    }
}