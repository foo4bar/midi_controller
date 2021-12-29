#ifndef MidiEventsSender_hpp
#define MidiEventsSender_hpp

#include <MIDI.h>

#include "Key.hpp"

namespace midictrl
{
    using namespace kbd;

    class MidiEventsSender
    {
    private:
        static inline constexpr uint8_t midiChannel{0};

    public:
        MidiEventsSender();

        void generate(const uint8_t midiNoteNumber,
                      const kbd::Key::State &actualKeyState,
                      const uint8_t keyVelocity) const;
    };
}

#endif