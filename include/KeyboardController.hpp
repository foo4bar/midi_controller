#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <stdint.h>
#include <ContactMatrices.hpp>

#include <vector>

namespace kbd
{
    enum class KeyEvent
    {
        depressed,
        released
    };

    class KeyboardController
    {
    private:
        static inline const uint8_t firstKeyMidiNoteNumber{21};
    };

}

#endif