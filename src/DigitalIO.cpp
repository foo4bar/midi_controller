#include "DigitalIO.hpp"

namespace arduino::digital
{
    void setPinMode(const uint8_t pinNumber, const Mode mode)
    {
        pinMode(pinNumber, static_cast<uint8_t>(mode));
    }

    const State getPinState(const uint8_t pinNumber)
    {
        return static_cast<State>(digitalRead(pinNumber));
    }

    void setPinState(const uint8_t pinNumber, const State state)
    {
        digitalWrite(pinNumber, static_cast<uint8_t>(state));
    }

    Pin::Pin(const uint8_t pin, const uint8_t port, const uint8_t number) : pin{pin}, port{port}, number{number} {}

    Pin::Pin() : pin{255}, port{255}, number{255} {} //TODO Get rid of the ctor.

    void Pin::setHigh()
    {
        this->port |= _BV(this->pin);
    }

    void Pin::setLow()
    {
        this->port &= ~_BV(this->pin);
    }

    const uint8_t Pin::getNumber() const
    {
        return this->number;
    }
}