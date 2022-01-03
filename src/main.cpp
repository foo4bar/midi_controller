#include "KeyboardMatrices.hpp"
#include "Key.hpp"
#include "KeyboardController.hpp"
#include "MidiControl.hpp"

void attachUsbDeviceIfAny()
{
#if defined(USBCON)
    USBDevice.attach();
#endif
}

kbd::KeyboardController buildKeyboardController()
{
    std::vector<kbd::Key> keys;
    for (uint8_t keyNumber = 0; keyNumber < kbdmatrix::numberOfScannedContactPairs; ++keyNumber)
    {
        keys.push_back(kbd::Key(
            keyNumber,
            [](const uint8_t keyNumber, const uint8_t velocity)
            { midictrl::MidiControl::sendNoteOn(keyNumber, velocity); },
            [](const uint8_t keyNumber, const uint8_t velocity)
            { midictrl::MidiControl::sendNoteOff(keyNumber, velocity); },
            [](const uint8_t zeroBasedNumber) -> uint8_t
            { return midictrl::MidiControl::getActualMidiNoteNumber(zeroBasedNumber); }));
    }

    return kbd::KeyboardController(keys);
}

void serialEventSafeRun()
{
    if (serialEventRun)
    {
        serialEventRun();
    }
}

int main()
{
    init();
    attachUsbDeviceIfAny();

    kbd::KeyboardController keyboardController{buildKeyboardController()};

    for (;;)
    {
        keyboardController.sendMidiEvents();
    }

    serialEventSafeRun();
}
