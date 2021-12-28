#ifndef Key_hpp
#define Key_hpp

#include "Contact.hpp"

namespace kbd
{
    //Each key is served by a pair of contacts.
    //One of them is closed first when a corresponding key starts to be pressed,
    //another one is closed last when the key is fully depressed.
    //
    class Key
    {
    private:
        ContactPair contacts{};

    public:
        enum class State
        {
            depressed,
            halfReleased,
            released
        };
    };
}

#endif