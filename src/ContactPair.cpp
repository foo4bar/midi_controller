#include "ContactPair.hpp"
#include "KeyboardMatrices.hpp"

namespace kbd
{
    ContactPair::ContactPair(const uint8_t number) : number{number}
    {
    }

    void ContactPair::updateStateWithDebouncing()
    {
        const arduino::digital::StatePair statePair{getActualInstantaneousInputStatePair(this->number)};
        this->firstClosed.updateStateWithDebouncing(digitalStateToContactState(statePair.firstClosed));
        this->lastClosed.updateStateWithDebouncing(digitalStateToContactState(statePair.lastClosed));
    }

    const Contact::State ContactPair::digitalStateToContactState(const arduino::digital::State &digitalState) const
    {
        return digitalState == arduino::digital::State::high
                   ? Contact::State::open
                   : Contact::State::closed;
    }
}