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

        const uint8_t getPressingTimeMillis() const;

        const uint8_t getReleasingTimeMillis() const;

        const bool isAsKeyDepressed() const;

        const bool isAsKeyReleases() const;

        const bool isAsKeyHalfReleased() const;
    };
}

#endif