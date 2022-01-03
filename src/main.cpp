#include <MIDI.h>

#include "KeyboardMatrices.hpp"
#include "Key.hpp"
#include "KeyboardController.hpp"

MIDI_CREATE_DEFAULT_INSTANCE()

//Copied from the framework main() implementation.
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

auto buildKeyboardController()
{
    std::vector<kbd::Key> keys;
    for (uint8_t keyNumber{0}; keyNumber < kbdmatrix::numberOfScannedContactPairs; ++keyNumber)
    {
        keys.push_back(kbd::Key{keyNumber, &MIDI});
    }

    return kbd::KeyboardController{keys};
}

//Copied from the framework main() implementation.
void serialEventSafeRun()
{
    if (serialEventRun)
    {
        serialEventRun();
    }
}

int main()
{
    //Copied from the framework main() implementation.
    init();

    attachUsbDeviceIfAny();

    initMidiInterface();

    auto keyboardController{buildKeyboardController()};
    for (;;)
    {
        keyboardController.sendMidiEvents();
    }

    serialEventSafeRun();
}
