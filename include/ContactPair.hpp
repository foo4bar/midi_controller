#ifndef ContactPair_hpp
#define ContactPair_hpp

#include <stdint.h>

#include "Contact.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    class ContactPair
    {
    public:
        Contact firstClosed;
        Contact lastClosed;

        ContactPair(const uint8_t number);

        void updateStateWithDebouncing();

    private:
        uint8_t number;
    };
}

#endif