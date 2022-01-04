#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include "Key.hpp"

namespace kbd
{
    class KeyboardController
    {
    private:
        static inline constexpr uint8_t firstKeyMidiNoteNumber{21};
        static inline constexpr uint8_t midiChannel{1};

        std::vector<Key> keys;

    public:
        KeyboardController(const std::vector<Key> &);

        void sendMidiEvents();
    };
}

#endif