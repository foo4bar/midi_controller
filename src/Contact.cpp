#include <Contact.hpp>
#include <Time.hpp>

namespace kbd
{
    using namespace arduino;

    const bool Contact::isBounsingFinished(const unsigned long timeFromStartMillis) const
    {
        return (timeFromStartMillis - this->lastTimeStateChangedMillis) > Contact::maxBouncingTimeMillis;
    }

    const bool Contact::isStateChanged(const Contact::State instantaneousContactState)
    {
        const unsigned long timeFromStartMillis = getTimeFromStartMillis();

        if (this->lastDetectedState == instantaneousContactState)
        {
            if (this->steadyState == this->lastDetectedState)
            {
                return false;
            }
            else
            {
                if (isBounsingFinished(timeFromStartMillis))
                {
                    this->steadyState = this->lastDetectedState;

                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            this->lastDetectedState = instantaneousContactState;
            this->lastTimeStateChangedMillis = timeFromStartMillis;

            return false;
        }
    }
}