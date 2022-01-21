#include <Arduino.h>

#include "DigitalIO.hpp"

namespace arduino::digital
{
    AvrPin::AvrPin(const uint8_t arduinoPinNumber) : bitMask{digitalPinToBitMask(arduinoPinNumber)},
                                                     port{digitalPinToPort(arduinoPinNumber)},
                                                     inputRegister{portInputRegister(port)},
                                                     outputRegister{portOutputRegister(port)},
                                                     modeRegister{portModeRegister(port)}
    {
    }

    void AvrPin::setState(const State state) const
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
            //Do nothing
            break;
        }
    }

    const State AvrPin::getState() const
    {
        return (*this->inputRegister & this->bitMask) ? State::high : State::low;
    }

    void AvrPin::setMode(const Mode mode) const
    {
        switch (mode)
        {
        case Mode::input:
            doWithDisabledInterrupts([](const AvrPin &pin)
                                     {
                                         *pin.modeRegister = *pin.modeRegister & ~pin.bitMask;
                                         *pin.outputRegister = *pin.outputRegister & ~pin.bitMask;
                                     });
            break;

        case Mode::inputWithInternalPullUp:
            doWithDisabledInterrupts([](const AvrPin &pin)
                                     {
                                         *pin.modeRegister = *pin.modeRegister & ~pin.bitMask;
                                         *pin.outputRegister = *pin.outputRegister | pin.bitMask;
                                     });
            break;

        case Mode::output:
            doWithDisabledInterrupts([](const AvrPin &pin)
                                     { *pin.modeRegister = *pin.modeRegister | pin.bitMask; });
            break;

        default:
            //Do nothing
            break;
        }
    }

    void AvrPin::doWithDisabledInterrupts(void (*function)(const AvrPin &pin)) const
    {
        uint8_t oldSREG = SREG;
        cli();

        function(*this);

        SREG = oldSREG;
    }
}