#ifndef DigitalIO_hpp
#define DigitalIO_hpp

#include <array>

#include <stdint.h>

namespace arduino::digital
{

    static inline constexpr uint8_t numberOfPins{54};

    enum class State : uint8_t
    {
        low = 0, // LOW in Arduino.h
        high = 1 // HIGH in Arduino.h
    };

    enum class Mode : uint8_t
    {
        input = 0,                  // INPUT in Arduino.h
        output = 1,                 // OUTPUT in Arduino.h
        inputWithInternalPullUp = 2 // INPUT_PULLUP in Arduino.h
    };

    class AvrPin
    {
    public:
        AvrPin(const uint8_t arduinoPinNumber);

        void setState(const State);
        const State getState() const;
        void setMode(const Mode);

    private:
        uint8_t bitMask;
        uint8_t port;
        volatile uint8_t *inputRegister;
        volatile uint8_t *outputRegister;
        volatile uint8_t *modeRegister;

        void doWithDisabledInterrupts(void (*function)(AvrPin &));
    };

    struct InputStatePair
    {
        State withFirstClosedContactOutput{State::high};
        State withLastClosedContactOutput{State::high};
    };
}

#endif