#ifndef MidiEventsGenerator_hpp
#define MidiEventsGenerator_hpp

#include <array>

#include <HardwareSerial.h>
#include <MIDI.h>

#include "Key.hpp"
#include "DigitalIO.hpp"

namespace midi
{
    class MidiEventsGenerator
    {
    public:
        MidiEventsGenerator();

        void generate(const std::array<kbd::Key, arduino::digital::numberOfScannedContactPairs> &keys) const;
    };
}

#endif