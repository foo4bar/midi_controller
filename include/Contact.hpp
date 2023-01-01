#ifndef Contact_hpp
#define Contact_hpp

#include <stdint.h>

#include "DigitalIO.hpp"

namespace kbd
{
    class Contact
    {
    public:
        Contact();
        Contact(const char *(*debugOutput)());

        void updateStateWithDebouncing(const arduino::digital::State actualInstantaneousState);

        bool isClosed() const;

        unsigned long getLastTimeStateChangedMillis() const;

    private:
        enum class State : uint8_t
        {
            open = 0,
            closed = 1
        };

        static inline const unsigned long maxBouncingTimeMillis{3}; // TODO Check with 2 ms.

        State actualSteadyState{State::open};
        State lastDetectedInstantaneousState{State::open};
        unsigned long lastTimeStateChangedMillis{0};

        bool isBounsingFinished(const unsigned long timeFromStartMillis) const;

        const char *(*debugOutput)() = []()
        {
            return "";
        };
    };
}

#endif