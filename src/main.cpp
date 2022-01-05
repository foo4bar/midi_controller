#include <MIDI.h>

#include "KeyboardMatrices.hpp"
#include "KeyboardController.hpp"

MIDI_CREATE_DEFAULT_INSTANCE()

//Copied as is from the Arduino framework main() implementation.
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

//Copied as is from the Arduino framework main() implementation.
void serialEventSafeRun()
{
    if (serialEventRun)
    {
        serialEventRun();
    }
}

int main()
{
    //Copied as is from the Arduino framework main() implementation.
    init();

    attachUsbDeviceIfAny();

    initMidiInterface();

    auto keyboardController{kbd::KeyboardController::Builder{}
                                .withfirstKeyMidiNoteNumber(21)
                                .withMidiChannel(0)
                                .withNumberOfKeys(kbdmatrix::numberOfScannedKeys)
                                .build()};
    for (;;)
    {
        keyboardController.sendMidiEvents(MIDI);
    }

    serialEventSafeRun();
}
