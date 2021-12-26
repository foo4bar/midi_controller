#ifndef MidiEventsGenerator_hpp
#define MidiEventsGenerator_hpp

#include <vector>

#include <MIDI.h>

#include "Key.hpp"

namespace midi
{
    class MidiEventsGenerator
    {
    public:
        MidiEventsGenerator();

        void generate(const std::vector<kbd::Key> &keys) const;
    };
}

#endif