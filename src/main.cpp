#ifdef DEBUG_MESSAGES
#include <string>
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

    auto keyboardController{kbd::KeyboardController::Builder{}
                                .withfirstKeyMidiNoteNumber(21)
                                .withMidiChannel(1)
                                .withNumberOfKeys(kbdmatrix::numberOfScannedKeys)
                                .build()};
#ifdef DEBUG_MESSAGES
    long counter{};
    char buffer[100];
#endif
    for (;;)
    {
#ifdef DEBUG_MESSAGES
        ++counter;
        if (counter == 1'000)
        {
            counter = 0;
            Serial.write(std::basic_string("1k cicles executed: timeFromStartMillis=")
                             .append(ltoa(arduino::getTimeFromStartMillis(), buffer, 10))
                             .append("\n")
                             .c_str());
        }
#endif
        keyboardController.sendMidiEvents(MIDI);
    }

    serialEventSafeRun();
}
