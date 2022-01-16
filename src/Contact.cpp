#include <Arduino.h>

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
        const auto timeFromStartMillis = millis();

        if (this->lastDetectedInstantaneousState == actualInstantaneousState)
        {
            if (this->actualSteadyState != this->lastDetectedInstantaneousState &&
                isBounsingFinished(timeFromStartMillis))
            {
                this->actualSteadyState = this->lastDetectedInstantaneousState;
            }
            else
            {
                // Do nothing.
            }
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