#include "ContactPair.hpp"

namespace kbd
{
    void ContactPair::updateStateWithDebouncing(const uint8_t number)
    {
        const auto inputStatePair{kbdmatrix::getActualInstantaneousInputStatePair(number)};
        this->firstClosed.updateStateWithDebouncing(inputStatePair.withFirstClosedContactOutput);
        this->lastClosed.updateStateWithDebouncing(inputStatePair.withLastClosedContactOutput);
    }

    const uint8_t ContactPair::getPressingTimeMillis() const
    {
        return this->firstClosed.getLastTimeStateChangedMillis() - this->lastClosed.getLastTimeStateChangedMillis();
    }

    const uint8_t ContactPair::getReleasingTimeMillis() const
    {
        return this->lastClosed.getLastTimeStateChangedMillis() - this->firstClosed.getLastTimeStateChangedMillis();
    }

    const bool ContactPair::isAsKeyDepressed() const
    {
        return this->firstClosed.isClosed() && this->lastClosed.isClosed();
    }

    const bool ContactPair::isAsKeyReleases() const
    {
        return !this->firstClosed.isClosed() && !this->lastClosed.isClosed();
    }

    const bool ContactPair::isAsKeyHalfReleased() const
    {
        return this->firstClosed.isClosed() && !this->lastClosed.isClosed();
    }
}