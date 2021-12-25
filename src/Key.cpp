#include <Key.hpp>

namespace kbd
{
    Key::Key(const Contact &firstClosedContact,
             const Contact &lastClosedContact) : firstClosedContact{firstClosedContact},
                                                 lastClosedContact{lastClosedContact}
    {
    }

    Key::Builder &Key::Builder::withFirstClosedContact(const Contact &contact)
    {
        this->firstClosedContact = contact;
        return *this;
    }

    Key::Builder &Key::Builder::withLastClosedContact(const Contact &contact)
    {
        this->lastClosedContact = contact;
        return *this;
    }

    Key Key::Builder::build() const
    {
        return Key{firstClosedContact, lastClosedContact};
    }
}