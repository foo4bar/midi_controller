#ifndef DigitalIO_hpp
#define DigitalIO_hpp

#include <array>

#include <stdint.h>

//Serves as a kind of HAL to decouple of C stuff in Arduino.h.
namespace arduino::digital
{
    enum class State : uint8_t
    {
        low = 0, //LOW in Arduino.h
        high = 1 //HIGH in Arduino.h
    };

    enum class Mode : uint8_t
    {
        input = 0,                  //INPUT in Arduino.h
        output = 1,                 //OUTPUT in Arduino.h
        inputWithInternalPullUp = 2 //INPUT_PULLUP in Arduino.h
    };

    class Pin
    {
    private:
        uint8_t bitMask;
        uint8_t port;
        volatile uint8_t *inputRegister;
        volatile uint8_t *outputRegister;
        volatile uint8_t *modeRegister;

        void doWithDisabledInterrupts(void (*function)(Pin));

    public:
        Pin();
        Pin(const uint8_t number);

        void setState(const State);
        const State getState();
        void setMode(const Mode);
    };

    struct InputStatePair
    {
        State withFirstClosedContactOutput{State::high};
        State withLastClosedContactOutput{State::high};
    };
}

#endif