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

    Pin::Pin(const uint8_t arduinoPinNumber, const Mode mode) : Pin(arduinoPinNumber)
    {
        this->setMode(mode);
    }

    Pin::Pin(const uint8_t arduinoPinNumber, const Mode mode, const State initialState) : Pin(arduinoPinNumber, mode)
    {
        this->setState(initialState);
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
}
