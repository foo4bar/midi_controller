#ifndef DigitalIO_hpp
#define DigitalIO_hpp

#include <map>
#include <vector>

#include <stdint.h>

namespace arduino::digital
{

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

    class Pin
    {
    public:
        explicit Pin(const uint8_t arduinoPinNumber);

        void setState(const State) const;
        State getState() const;
        void setMode(const Mode) const;

    private:
        uint8_t number;
        uint8_t bitMask;
        uint8_t port;
        volatile uint8_t *const inputRegister;
        volatile uint8_t *const outputRegister;
        volatile uint8_t *const modeRegister;

        void doWithDisabledInterrupts(void (*function)(const Pin &)) const;
    };

    class Pins
    {
    public:
        explicit Pins(const std::map<Mode, std::vector<uint8_t>> &modeToPinMapping);
        Pin operator[](const uint8_t pinNumber) const;

    private:
        std::map<uint8_t, Pin> pins;
    };

    struct KeyInputStates
    {
        State withFirstActuatedContactOutput{State::high};
        State withLastActuatedContactOutput{State::high};
    };

    struct KeyGroupOutputs
    {
        Pin firstActuatedContactOutput;
        Pin lastActuatedContactOutput;
    };
}

#endif