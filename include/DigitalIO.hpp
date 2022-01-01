#ifndef DigitalIO_hpp
#define DigitalIO_hpp

#include <stdint.h>

//Serves as a kind of HAL to decouple of C stuff in Arduino.h.
namespace arduino::digital
{   
    enum class State : uint8_t
    {
        low = 0, //LOW in Arduino.h
        high = 1 //HIGH in Arduino.h
    };

    struct StatePair
    {
        State firstClosed{State::high};
        State lastClosed{State::high};
    };

    enum class Mode : uint8_t
    {
        input = 0,                  //INPUT in Arduino.h
        output = 1,                 //OUTPUT in Arduino.h
        inputWithInternalPullUp = 2 //INPUT_PULLUP in Arduino.h
    };

    void setPinMode(const uint8_t pinNumber, const Mode mode);

    const State getPinState(const uint8_t pinNumber);

    void setPinState(const uint8_t pinNumber, const State state);
}

#endif