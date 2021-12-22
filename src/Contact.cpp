#include <Contact.hpp>
#include <Time.hpp>

namespace kbd
{
    using namespace arduino;

    const bool Contact::isBounsingFinished(const unsigned long timeFromStartMillis) const
    {
        return (timeFromStartMillis - this->lastTimeStateChangedMillis) > Contact::maxBouncingTimeMillis;
    }

    void Contact::debounce(const Contact::State instantaneousContactState)
    {
        const unsigned long timeFromStartMillis = getTimeFromStartMillis();
        if (this->lastDetectedState == instantaneousContactState)
        {
            if (this->steadyState != this->lastDetectedState && isBounsingFinished(timeFromStartMillis))
            {
                this->steadyState = this->lastDetectedState;
                this->lastDetectedState = instantaneousContactState;
                //TODO
            }
        }
        else
        {
            this->lastTimeStateChangedMillis = timeFromStartMillis;
            this->lastDetectedState = instantaneousContactState;
        }
    }
}