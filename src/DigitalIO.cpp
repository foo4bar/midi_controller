#include <DigitalIO.hpp>
// Arduino.h is to be included right here, not in the header.
#include <Arduino.h>

namespace arduino
{
    namespace digital
    {
        void setPinMode(const uint8_t pinNumber, const Mode mode)
        {
            pinMode(pinNumber, static_cast<uint8_t>(mode));
        }

        State getPinState(const uint8_t pinNumber)
        {
            return static_cast<State>(digitalRead(pinNumber));
        }

        void setPinState(const uint8_t pinNumber, const State state)
        {
            digitalWrite(pinNumber, static_cast<uint8_t>(state));
        }
    }
}