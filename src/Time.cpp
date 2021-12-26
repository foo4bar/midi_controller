// Arduino.h is to be included right here, not in the header.
#include <Arduino.h>

#include "Time.hpp"

namespace arduino
{
    unsigned long getTimeFromStartMillis()
    {
        return millis();
    }
}