#ifndef Key_hpp
#define Key_hpp

#include "ContactPair.hpp"
#include "Midi.hpp"

namespace kbd
{
    class Key
    {
    public:
        enum class State
        {
            depressed,
            halfPressed,
            released
        };

        Key(const uint8_t);

        void sendMidiEvent();

    private:
        // Each key operates a pair of contacts.
        // One of them is closed first when a corresponding key starts to be pressed,
        // another one is closed last when the key is fully depressed.
        // Key state is defined by its contacts state.
        ContactPair contacts;
        State previousState{State::released};
        State actualState{State::released};
        uint8_t velocity{0};
    };
}

#endif