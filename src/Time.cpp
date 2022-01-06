#include <Arduino.h>

#include "Time.hpp"

namespace arduino
{
    unsigned long getTimeFromStartMillis()
    {
        return millis();
    }
}