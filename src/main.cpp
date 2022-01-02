#include "KeyboardMatrices.hpp"
#include "Key.hpp"
#include "KeyboardController.hpp"

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
        keys.push_back(kbd::Key(keyNumber));
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
