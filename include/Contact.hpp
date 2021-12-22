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

        void debounce(const Contact::State instantaneousContactState);

    private:
        static const unsigned long maxBouncingTimeMillis{1};

        State steadyState{State::open};
        State lastDetectedState{State::open};
        unsigned long lastTimeStateChangedMillis{0};

        const bool isBounsingFinished(const unsigned long timeFromStartMillis) const;
    };
}

#endif