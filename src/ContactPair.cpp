#include "ContactPair.hpp"

namespace kbd
{
    ContactPair::ContactPair(const uint8_t number) : number{number}
    {
    }

    void ContactPair::updateStateWithDebouncing()
    {
        const auto inputStatePair{kbdmatrix::getActualInstantaneousInputStatePair(this->number)};
        this->firstClosed.updateStateWithDebouncing(inputStatePair.withFirstClosedContactOutput);
        this->lastClosed.updateStateWithDebouncing(inputStatePair.withLastClosedContactOutput);
    }
}