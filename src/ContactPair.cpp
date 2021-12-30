#include "ContactPair.hpp"

namespace kbd
{
    ContactPair::ContactPair(const uint8_t number) : number{number}
    {
    }

    void ContactPair::updateStateWithDebouncing()
    {
        const arduino::digital::StatePair statePair{arduino::digital::getActualInstantaneousInputStatePair(this->number)};
        this->firstClosed.updateStateWithDebouncing(statePair.firstClosed == arduino::digital::State::high
                                                        ? Contact::State::open
                                                        : Contact::State::closed);
        this->lastClosed.updateStateWithDebouncing(statePair.lastClosed == arduino::digital::State::high
                                                       ? Contact::State::open
                                                       : Contact::State::closed);
    }
}