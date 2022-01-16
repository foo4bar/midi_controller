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

    void AvrPin::setState(const State state)
    {
        //The portOutputRegister macros is about 0.25ms slower than the member variable.
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

    const State AvrPin::getState()
    {
        //The portInputRegister macros is about 0.2ms faster than a member variable.
        return (*portInputRegister(this->port) & this->bitMask) ? State::high : State::low;
    }

    void AvrPin::setMode(const Mode mode)
    {
        switch (mode)
        {
        case Mode::input:
            doWithDisabledInterrupts([](AvrPin pin)
                                     {
                                         *pin.modeRegister = *pin.modeRegister & ~pin.bitMask;
                                         *pin.outputRegister = *pin.outputRegister & ~pin.bitMask;
                                     });
            break;

        case Mode::inputWithInternalPullUp:
            doWithDisabledInterrupts([](AvrPin pin)
                                     {
                                         *pin.modeRegister = *pin.modeRegister & ~pin.bitMask;
                                         *pin.outputRegister = *pin.outputRegister | pin.bitMask;
                                     });
            break;

        case Mode::output:
            doWithDisabledInterrupts([](AvrPin pin)
                                     { *pin.modeRegister = *pin.modeRegister | pin.bitMask; });
            break;

        default:
            //Do nothing
            break;
        }
    }

    void AvrPin::doWithDisabledInterrupts(void (*function)(AvrPin pin))
    {
        uint8_t oldSREG = SREG;
        cli();

        function(*this);

        SREG = oldSREG;
    }
}