#ifndef Key_hpp
#define Key_hpp

#include "ContactPair.hpp"

namespace kbd
{
    // Each key operates a pair of contacts.
    // One of them is closed first when a corresponding key starts to be pressed,
    // another one is closed last when the key is fully depressed.
    //
    class Key
    {
    public:
        enum class State
        {
            depressed,
            halfPressed,
            released
        };

        const State &getActualState() const;
        const uint8_t getVelocity() const;
        const uint8_t getNumber() const;

        const bool isSateChanged();
        void resetStateChange();

        Key(const uint8_t number);

    private:
        uint8_t number;
        ContactPair contacts;
        State previousState{State::released};
        State actualState{State::released};
        uint8_t velocity{0};
    };
}

#endif