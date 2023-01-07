
#ifdef CYCLE_TIME_DEBUG_MESSAGES
#include <Arduino.h>
#endif

#ifdef AVR_STUB_DEBUG
#include <avr8-stub.h>
#endif

#include "KeyboardController.hpp"

using namespace kbd;

void initAvrStubDebug();
void attachUsbDevice();
void sendMidiEvents(KeyboardController &);
void serialEventSafeRun();

int main()
{
    init();
    initAvrStubDebug();
    attachUsbDevice();

    KeyboardController controller{};

    sendMidiEvents(controller);
    serialEventSafeRun();
}

void initAvrStubDebug()
{
#ifdef AVR_STUB_DEBUG
    debug_init();
#endif
}

void attachUsbDevice()
{
// Copied as is from the Arduino framework main() implementation.
#ifdef USBCON
    USBDevice.attach();
#endif
}

void sendMidiEvents(KeyboardController &keyboardController)
{
#ifdef CYCLE_TIME_DEBUG_MESSAGES
    long counter{};
    char buffer[100];
#endif

    for (;;)
    {
        keyboardController.sendMidiEvents();

#ifdef CYCLE_TIME_DEBUG_MESSAGES
        ++counter;
        if (counter == 10'000)
        {
            counter = 0;
            Serial.write("10k of cycles were executed: timeFromStartMillis=");
            Serial.write(ltoa(millis(), buffer, 10));
            Serial.write("\n");
        }
#endif
    }
}

void serialEventSafeRun()
{
    // Copied as is from the Arduino framework main() implementation.
    if (serialEventRun)
    {
        serialEventRun();
    }
}
