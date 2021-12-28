#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <array>

#include <stdint.h>

#include "Key.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    class KeyboardController
    {
    private:
        static inline const uint8_t firstKeyMidiNoteNumber{21};

        std::array<Key, arduino::digital::numberOfServedContactPairs> keys;

    public:
        const std::array<Key, arduino::digital::numberOfServedContactPairs> &getKeys() const;
    };

}

#endif