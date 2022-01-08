#ifdef DEBUG_MESSAGES
#include <string>
#include <HardwareSerial.h>
#endif

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

        if (this->lastDetectedInstantaneousState == actualInstantaneousState)
        {
            if (this->actualSteadyState != this->lastDetectedInstantaneousState &&
                isBounsingFinished(timeFromStartMillis))
            {
#ifdef DEBUG_MESSAGES
                char buffer[100];
                Serial.write(std::basic_string("Sate changed: actualSteadyState=")
                                 .append(itoa((uint8_t)this->actualSteadyState, buffer, 10))
                                 .append(", lastDetectedInstantaneousState=")
                                 .append(itoa((uint8_t)this->lastDetectedInstantaneousState, buffer, 10))
                                 .append(", lastTimeStateChangedMillis=")
                                 .append(ltoa(this->lastTimeStateChangedMillis, buffer, 10))
                                 .append(", timeFromStartMillis=")
                                 .append(ltoa(timeFromStartMillis, buffer, 10))
                                 .append("\n")
                                 .c_str());
#endif
                this->actualSteadyState = this->lastDetectedInstantaneousState;
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
#ifdef DEBUG_MESSAGES
            char buffer[100];
            Serial.write(std::basic_string("Bouncing: actualInstantaneousState=")
                             .append(itoa((uint8_t)actualInstantaneousState, buffer, 10))
                             .append(", timeFromStartMillis=")
                             .append(ltoa(timeFromStartMillis, buffer, 10))
                             .append("\n")
                             .c_str());
#endif
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