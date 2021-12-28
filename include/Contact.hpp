#ifndef Contact_hpp
#define Contact_hpp

#include <stdint.h>

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

        void updateStateWithDebouncing(const Contact::State actualInstantaneousState);

    private:
        static const unsigned long maxBouncingTimeMillis{1};

        State previousSteadyState{State::open};
        State actualSteadyState{State::open};
        State lastDetectedInstantaneousState{State::open};
        unsigned long lastTimeStateChangedMillis{0};

        bool isBounsingFinished(const unsigned long timeFromStartMillis) const;
    };

    struct ContactPair
    {
        Contact firstClosed;
        Contact lastClosed;
    };

    struct ContactPairState
    {
        Contact::State firstClosed;
        Contact::State lastClosed;
    };
}

#endif