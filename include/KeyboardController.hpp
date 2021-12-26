#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <stdint.h>

#include "Contacts.hpp"
#include "Key.hpp"

namespace kbd
{
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