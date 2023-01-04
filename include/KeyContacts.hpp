#ifndef KeyContacts_hpp
#define KeyContacts_hpp

#include <stdint.h>

#include "Contact.hpp"
#include "KeyboardMatricesIO.hpp"

namespace kbd
{
    class KeyContacts
    {
    public:
        explicit KeyContacts(const uint8_t number);

        void updateStateWithDebouncing(const KeyboardMatricesIO &);

        unsigned long getKeyPressingTimeMillis() const;

        bool isAsKeyIsDepressed() const;

        bool isAsKeyIsReleased() const;

    private:
        uint8_t number;

        // One of contacts is actuated first when a corresponding key is just pressed down a bit,
        // another one is actuated last when the key is almost fully depressed.

        Contact firstActuated{Contact{[]()
                                      {
                                          return "first, ";
                                      }}};
        Contact lastActuated{Contact{[]()
                                     {
                                         return "last, ";
                                     }}};
    };
}

#endif