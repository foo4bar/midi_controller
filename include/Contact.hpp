#ifndef Contact_hpp
#define Contact_hpp

#include <stdint.h>

#include "Time.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    class Contact
    {
    public:
        enum class State : uint8_t
        {
            open = 0,
            closed = 1
        };

        void updateStateWithDebouncing(const arduino::digital::State actualInstantaneousState);

        bool isClosed() const;

        unsigned long getLastTimeStateChangedMillis() const;

    private:
        static const unsigned long maxBouncingTimeMillis{1};

        State previousSteadyState{State::open};
        State actualSteadyState{State::open};
        State lastDetectedInstantaneousState{State::open};
        unsigned long lastTimeStateChangedMillis{0};

        bool isBounsingFinished(const unsigned long timeFromStartMillis) const;
    };
}

#endif