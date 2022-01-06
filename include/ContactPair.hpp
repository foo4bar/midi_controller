#ifndef ContactPair_hpp
#define ContactPair_hpp

#include <stdint.h>

#include "Contact.hpp"
#include "KeyboardMatrices.hpp"

namespace kbd
{
    class ContactPair
    {
    private:
        // One of contacts is closed first when a corresponding key starts to be pressed,
        // another one is closed last when the key is fully depressed.
        Contact firstClosed;
        Contact lastClosed;

    public:
        void updateStateWithDebouncing(const uint8_t keyNumber);

        const unsigned long getPressingTimeMillis() const;

        const unsigned long getReleasingTimeMillis() const;

        const bool isAsKeyIsDepressed() const;

        const bool isAsKeyIsReleased() const;

        const bool isAsKeyIsHalfReleased() const;
    };
}

#endif