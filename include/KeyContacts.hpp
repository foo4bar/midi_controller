#ifndef KeyContacts_hpp
#define KeyContacts_hpp

#include "Contact.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    class KeyContacts
    {
    public:
        void updateStateWithDebouncing(const arduino::digital::KeyInputStates &);

        unsigned long getKeyPressingTimeMillis() const;

        bool isAsKeyIsDepressed() const;

        bool isAsKeyIsReleased() const;

    private:
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