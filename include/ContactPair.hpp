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
        Contact firstClosed;
        Contact lastClosed;

    public:
        void updateStateWithDebouncing(const uint8_t);

        const unsigned long getPressingTimeMillis() const;

        const unsigned long getReleasingTimeMillis() const;

        const bool isAsKeyIsDepressed() const;

        const bool isAsKeyIsReleased() const;

        const bool isAsKeyIsHalfReleased() const;
    };
}

#endif