#include <Arduino.h>

#include "DigitalIO.hpp"

namespace arduino::digital
{
    Pin::Pin()
    {
    }

    Pin::Pin(const uint8_t number) : bitMask{digitalPinToBitMask(number)},
                                     port{digitalPinToPort(number)},
                                     inputRegister{portInputRegister(port)},
                                     outputRegister{portOutputRegister(port)},
                                     modeRegister{portModeRegister(port)}
    {
    }

    void Pin::setState(const State state)
    {
        if (state == State::high)
        {
            *this->outputRegister |= this->bitMask;
        }
        else if (state == State::low)
        {
            *this->outputRegister &= ~this->bitMask;
        }
    }

    const State Pin::getState()
    {
        if (*this->inputRegister & this->bitMask)
        {
            return State::high;
        }
        else
        {
            return State::low;
        }
    }

    void Pin::setMode(const Mode mode)
    {
        switch (mode)
        {
        case Mode::input:
            doWithDisabledInterrupts([](Pin pin)
                                     {
                                         *pin.modeRegister &= ~pin.bitMask;
                                         *pin.outputRegister &= ~pin.bitMask;
                                     });
            break;

        case Mode::inputWithInternalPullUp:
            doWithDisabledInterrupts([](Pin pin)
                                     {
                                         *pin.modeRegister &= ~pin.bitMask;
                                         *pin.outputRegister |= pin.bitMask;
                                     });
            break;

        case Mode::output:
            doWithDisabledInterrupts([](Pin pin)
                                     { *pin.modeRegister |= pin.bitMask; });
            break;

        default:
            break;
        }
    }

    void Pin::doWithDisabledInterrupts(void (*function)(Pin pin))
    {
        uint8_t oldSREG = SREG;
        cli();

        function(*this);

        SREG = oldSREG;
    }
}