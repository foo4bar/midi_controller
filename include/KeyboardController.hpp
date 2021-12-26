#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <stdint.h>

#include "ContactMatrices.hpp"
#include "Key.hpp"

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

        std::vector<Key> keys;

    public:
        const std::vector<Key> &getKeys() const;
    };

}

#endif