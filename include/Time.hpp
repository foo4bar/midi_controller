#ifndef Time_hpp
#define Time_hpp

//Serves as a kind of HAL to decouple of C stuff in Arduino.h.
namespace arduino
{
    unsigned long getTimeFromStartMillis();
}

#endif