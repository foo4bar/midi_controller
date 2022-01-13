#ifdef CYCLE_TIME_DEBUG_MESSAGES
#include <Time.hpp>
#endif

#include <MIDI.h>
#include <Arduino.h>

#include "KeyboardMatrices.hpp"
#include "KeyboardController.hpp"

MIDI_CREATE_DEFAULT_INSTANCE()

// Copied as is from the Arduino framework main() implementation.
void attachUsbDeviceIfAny()
{
#if defined(USBCON)
    USBDevice.attach();
#endif
}

void initMidiInterface()
{
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

// Copied as is from the Arduino framework main() implementation.
void serialEventSafeRun()
{
    if (serialEventRun)
    {
        serialEventRun();
    }
}

int main()
{
    // Copied as is from the Arduino framework main() implementation.
    init();

    attachUsbDeviceIfAny();

    initMidiInterface();

    auto keyboardController{kbd::KeyboardController::Builder{.firstKeyMidiNoteNumber{21},
                                                             .midiChannel{1},
                                                             .numberOfKeys{kbd::numberOfScannedKeys}}
                                .build()};
#ifdef CYCLE_TIME_DEBUG_MESSAGES
    long counter{};
    char buffer[100];
#endif
    for (;;)
    {
#ifdef CYCLE_TIME_DEBUG_MESSAGES
        ++counter;
        if (counter == 1'000)
        {
            counter = 0;
            Serial.write("1k cicles executed: timeFromStartMillis=");
            Serial.write(ltoa(arduino::getTimeFromStartMillis(), buffer, 10));
            Serial.write("\n");
        }
#endif
        keyboardController.sendMidiEvents(MIDI);
    }

    serialEventSafeRun();
}
