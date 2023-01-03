#include <Arduino.h>

#include "DigitalIO.hpp"

namespace arduino::digital
{
    Pin::Pin(const uint8_t arduinoPinNumber) : number{arduinoPinNumber},
                                               bitMask{digitalPinToBitMask(arduinoPinNumber)},
                                               port{digitalPinToPort(arduinoPinNumber)},
                                               inputRegister{portInputRegister(port)},
                                               outputRegister{portOutputRegister(port)},
                                               modeRegister{portModeRegister(port)}
    {
    }

    void Pin::setState(const State state) const
    {
        switch (state)
        {
        case State::high:
            *this->outputRegister = *this->outputRegister | this->bitMask;
            break;

        case State::low:
            *this->outputRegister = *this->outputRegister & ~this->bitMask;
            break;

        default:
            // Do nothing
            break;
        }
    }

    State Pin::getState() const
    {
        return (*this->inputRegister & this->bitMask) ? State::high : State::low;
    }

    void Pin::setMode(const Mode mode) const
    {
        switch (mode)
        {
        case Mode::input:
            doWithDisabledInterrupts([](const Pin &pin)
                                     {
                                         *pin.modeRegister = *pin.modeRegister & ~pin.bitMask;
                                         *pin.outputRegister = *pin.outputRegister & ~pin.bitMask; });
            break;

        case Mode::inputWithInternalPullUp:
            doWithDisabledInterrupts([](const Pin &pin)
                                     {
                                         *pin.modeRegister = *pin.modeRegister & ~pin.bitMask;
                                         *pin.outputRegister = *pin.outputRegister | pin.bitMask; });
            break;

        case Mode::output:
            doWithDisabledInterrupts([](const Pin &pin)
                                     { *pin.modeRegister = *pin.modeRegister | pin.bitMask; });
            break;

        default:
            // Do nothing
            break;
        }
    }

    void Pin::doWithDisabledInterrupts(void (*function)(const Pin &pin)) const
    {
        const uint8_t oldSREG{SREG};
        cli();

        function(*this);

        SREG = oldSREG;
    }

    void PinMap::insert(const uint8_t pinNumber, const Pin pin)
    {
        this->pins.insert({pinNumber, pin});
    }

    Pin PinMap::operator[](const uint8_t pinNumber) const
    {
        return this->pins.find(pinNumber)->second;
    }
}