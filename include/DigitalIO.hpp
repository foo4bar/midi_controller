#ifndef DigitalIO_hpp
#define DigitalIO_hpp

#include <vector>

#include <Arduino.h>
#include <stdint.h>

//Serves as a kind of HAL to decouple of C stuff in Arduino.h.
namespace arduino::digital
{
    enum class State : uint8_t
    {
        low = 0, //LOW in Arduino.h
        high = 1 //HIGH in Arduino.h
    };

    class Pin
    {
    private:
        uint8_t pin;
        uint8_t port;
        uint8_t number;

    public:
        Pin(); //TODO Clarify why it's needed.
        Pin(const uint8_t pin, const uint8_t port, const uint8_t number);

        void setHigh();
        void setLow();
        //TODO consider to replace digitalRead() as well.

        const uint8_t getNumber() const;
    };

    static inline const std::vector<Pin> portA{Pin{PA0, PORTA, 22},
                                               Pin{PA1, PORTA, 23},
                                               Pin{PA2, PORTA, 24},
                                               Pin{PA3, PORTA, 25},
                                               Pin{PA4, PORTA, 26},
                                               Pin{PA5, PORTA, 27},
                                               Pin{PA6, PORTA, 28},
                                               Pin{PA7, PORTA, 29}};
    static inline const std::vector<Pin> portB{Pin{PB0, PORTB, 53},
                                               Pin{PB1, PORTB, 52},
                                               Pin{PB2, PORTB, 51},
                                               Pin{PB3, PORTB, 50}};
    static inline const std::vector<Pin> portC{Pin{PC0, PORTC, 37},
                                               Pin{PC1, PORTC, 36},
                                               Pin{PC2, PORTC, 35},
                                               Pin{PC3, PORTC, 34},
                                               Pin{PC4, PORTC, 33},
                                               Pin{PC5, PORTC, 32},
                                               Pin{PC6, PORTC, 31},
                                               Pin{PC7, PORTC, 30}};
    static inline const std::vector<Pin> portD{Pin{PD0, PORTD, 21},
                                               Pin{PD1, PORTD, 20},
                                               Pin{PD2, PORTD, 19},
                                               Pin{PD3, PORTD, 18},
                                               Pin{PD4, PORTD, 255}, //RX LED
                                               Pin{PD5, PORTD, 255}, //TX LED
                                               Pin{PD6, PORTD, 255}, //Not used.
                                               Pin{PD7, PORTD, 38}};
    static inline const std::vector<Pin> portE{Pin{PE0, PORTE, 0},
                                               Pin{PE1, PORTE, 1},
                                               Pin{PE2, PORTE, 255}, //Not used.
                                               Pin{PE3, PORTE, 5},
                                               Pin{PE4, PORTE, 2},
                                               Pin{PE5, PORTE, 3}};
    static inline const std::vector<Pin> portG{Pin{PG0, PORTG, 41},
                                               Pin{PG1, PORTG, 40},
                                               Pin{PG2, PORTG, 39},
                                               Pin{PG3, PORTG, 255}, //Not used.
                                               Pin{PG4, PORTG, 255}, //Not used.
                                               Pin{PG5, PORTG, 4}};
    static inline const std::vector<Pin> portH{Pin{PH0, PORTH, 17},
                                               Pin{PH1, PORTH, 16},
                                               Pin{PH2, PORTH, 255}, //Not used.
                                               Pin{PH3, PORTH, 6},
                                               Pin{PH4, PORTH, 7},
                                               Pin{PH5, PORTH, 8},
                                               Pin{PH6, PORTH, 9}};
    static inline const std::vector<Pin> portL{Pin{PL0, PORTL, 49},
                                               Pin{PL1, PORTL, 48},
                                               Pin{PL2, PORTL, 47},
                                               Pin{PL3, PORTL, 46},
                                               Pin{PL4, PORTL, 45},
                                               Pin{PL5, PORTL, 44},
                                               Pin{PL6, PORTL, 43},
                                               Pin{PL7, PORTL, 42}};

    struct InputStatePair
    {
        State withFirstClosedContactOutput{State::high};
        State withLastClosedContactOutput{State::high};
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