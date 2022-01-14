#ifndef ContactPair_hpp
#define ContactPair_hpp

#include <stdint.h>

#include "Contact.hpp"
#include "KeyboardMatricesIO.hpp"

namespace kbd
{
    class ContactPair
    {
    public:
        ContactPair(const uint8_t number);

        void updateStateWithDebouncing(KeyboardMatricesIO *const);

        const unsigned long getPressingTimeMillis() const;

        const unsigned long getReleasingTimeMillis() const;

        const bool isAsKeyIsDepressed() const;

        const bool isAsKeyIsReleased() const;

    private:
        // One of contacts is closed first when a corresponding key starts to be pressed,
        // another one is closed last when the key is fully depressed.
        Contact firstClosed;
        Contact lastClosed;

        uint8_t number;
    };
}

#endif