#include <Contact.hpp>
#include <Time.hpp>

namespace kbd
{
    using namespace arduino;

    const bool Contact::isBounsingFinished(const unsigned long timeFromStartMillis) const
    {
        return (timeFromStartMillis - this->lastTimeStateChangedMillis) > Contact::maxBouncingTimeMillis;
    }

    void Contact::updateStateWithDebouncing(const Contact::State actualInstantaneousState)
    {
        const unsigned long timeFromStartMillis = getTimeFromStartMillis();

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
}