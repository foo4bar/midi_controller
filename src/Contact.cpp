#include <Arduino.h>

#include "Contact.hpp"

namespace kbd
{
    Contact::Contact(const bool firstClosed, const uint8_t pairNumber) : firstClosed{firstClosed}, pairNumber{pairNumber}
    {
    }

    bool Contact::isBounsingFinished(const unsigned long timeFromStartMillis) const
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
            if (this->actualSteadyState != this->lastDetectedInstantaneousState && isBounsingFinished(timeFromStartMillis))
            {
                this->actualSteadyState = this->lastDetectedInstantaneousState;

#ifdef CONTACT_EVENTS_DEBUG_MESSAGES
                char buffer[10];
                Serial.write(itoa(this->pairNumber, buffer, 10));
                Serial.write(this->firstClosed ? ", first, " : ", last, ");
                Serial.write("actualSteadyState is ");
                Serial.write(this->actualSteadyState == State::closed ? "closed, " : "open, ");
                Serial.write("timeFromStartMillis is ");
                Serial.write(ltoa(timeFromStartMillis, buffer, 10));
                Serial.write("\n");
#endif
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

#ifdef CONTACT_EVENTS_DEBUG_MESSAGES
            char buffer[10];
            Serial.write(itoa(this->pairNumber, buffer, 10));
            Serial.write(this->firstClosed ? ", first, " : ", last, ");
            Serial.write("lastDetectedInstantaneousState is ");
            Serial.write(this->lastDetectedInstantaneousState == State::closed ? "closed, " : "open, ");
            Serial.write("timeFromStartMillis is ");
            Serial.write(ltoa(timeFromStartMillis, buffer, 10));
            Serial.write("\n");
#endif
        }
    }

    bool Contact::isClosed() const
    {
        return this->actualSteadyState == State::closed;
    }

    unsigned long Contact::getLastTimeStateChangedMillis() const
    {
        return this->lastTimeStateChangedMillis;
    }
}