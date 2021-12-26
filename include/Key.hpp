#ifndef Key_hpp
#define Key_hpp

#include "Contact.hpp"

namespace kbd
{
    class Key
    {
    private:
        Contact firstClosedContact;
        Contact lastClosedContact;

        Key(const Contact &firstClosedContact, const Contact &lastClosedContact);

    public:
        enum class State
        {
            depressed,
            halfReleased,
            released
        };

        class Builder
        {
        private:
            Contact firstClosedContact;
            Contact lastClosedContact;

        public:
            Builder &withFirstClosedContact(const Contact &contact);

            Builder &withLastClosedContact(const Contact &contact);

            Key build() const;
        };
    };

}

#endif