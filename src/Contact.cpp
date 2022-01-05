#include "Contact.hpp"

namespace kbd
{
    const bool Contact::isBounsingFinished(const unsigned long timeFromStartMillis) const
    {
        return (timeFromStartMillis - this->lastTimeStateChangedMillis) > Contact::maxBouncingTimeMillis;
    }

    
    
    void Contact::updateStateWithDebouncing(const arduino::digital::State actualInstantaneousInputState)
    {
        const auto actualInstantaneousState = actualInstantaneousInputState == arduino::digital::State::high
                                                  ? State::open
                                                  : State::closed;
        const auto timeFromStartMillis = arduino::getTimeFromStartMillis();

        if (this->lastDetectedInstantaneousState == actualInstantaneousState &&
            this->actualSteadyState != this->lastDetectedInstantaneousState &&
            isBounsingFinished(timeFromStartMillis))
        {
            this->previousSteadyState = this->actualSteadyState;
            this->actualSteadyState = this->lastDetectedInstantaneousState;
        }
        else
        {
            this->lastDetectedInstantaneousState = actualInstantaneousState;
            this->lastTimeStateChangedMillis = timeFromStartMillis;
        }
    }

    const bool Contact::isClosed() const
    {
        return this->actualSteadyState == State::closed;
    }

    const unsigned long Contact::getLastTimeStateChangedMillis() const
    {
        return this->lastTimeStateChangedMillis;
    }
}