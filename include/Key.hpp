#ifndef Key_hpp
#define Key_hpp

#include "Contact.hpp"

namespace kbd
{
    //Each key operates a pair of contacts.
    //One of them is closed first when a corresponding key starts to be pressed,
    //another one is closed last when the key is fully depressed.
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

        ContactPair contacts;
        uint8_t velocity{0};

        const bool isSateChanged();
        const State &getActualState() const;
        void resetStateChange();

    private:
        State previousState{State::released};
        State actualState{State::released};
    };
}

#endif