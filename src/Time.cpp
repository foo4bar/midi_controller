#include <Time.hpp>
// Arduino.h is to be included right here, not in the header.
#include <Arduino.h>

namespace arduino
{
    const unsigned long getTimeFromStartMillis()
    {
        return millis();
    }
}