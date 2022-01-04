#ifndef ContactPair_hpp
#define ContactPair_hpp

#include <stdint.h>

#include "Contact.hpp"
#include "KeyboardMatrices.hpp"

namespace kbd
{
    struct ContactPair
    {
        Contact firstClosed;
        Contact lastClosed;
        uint8_t number;

        ContactPair(const uint8_t);

        void updateStateWithDebouncing();
    };
}

#endif