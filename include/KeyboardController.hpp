#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <array>

#include <stdint.h>

#include "Key.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    using namespace arduino::digital;
    
    class KeyboardController
    {
    private:
        static inline const uint8_t firstKeyMidiNoteNumber{21};

        std::array<Key, numberOfScannedContactPairs> keys;

    public:
        const std::array<Key, numberOfScannedContactPairs> &updateKeysStateAndGet();
    };

}

#endif