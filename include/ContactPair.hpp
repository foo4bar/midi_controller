#ifndef ContactPair_hpp
#define ContactPair_hpp

#include <stdint.h>

#include "Contact.hpp"
#include "KeyboardMatrices.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    struct ContactPair
    {
    public:
        Contact firstClosed;
        Contact lastClosed;
        uint8_t number;

        ContactPair(const uint8_t);

        void updateStateWithDebouncing();

    private:
        const Contact::State digitalStateToContactState(const arduino::digital::State &) const;
    };
}

#endif