#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <stdint.h>

#include "Key.hpp"
#include "MidiEventsSender.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    class KeyboardController
    {
    private:
        static inline constexpr uint8_t firstKeyMidiNoteNumber{21};
        static inline constexpr uint8_t numberOfKeys{arduino::digital::numberOfScannedContactPairs};

        midictrl::MidiEventsSender midiEventsSender;
        std::vector<Key> keys;

    public:
        KeyboardController();

        void sendMidiEvents();
    };
}

#endif