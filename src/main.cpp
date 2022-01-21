#include <MIDI.h>
#include <Arduino.h>

#ifdef AVR_STUB_DEBUG
#include <avr8-stub.h>
#endif

#include "KeyboardMatricesIO.hpp"
#include "KeyboardController.hpp"
#include "DigitalIO.hpp"

#ifndef AVR_STUB_DEBUG
MIDI_CREATE_DEFAULT_INSTANCE()
#else
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI)
#endif

// Copied as is from the Arduino framework main() implementation.
void attachUsbDeviceIfAny()
{
#if defined(USBCON)
    USBDevice.attach();
#endif
}

void initMidiInterface()
{
#ifndef AVR_STUB_DEBUG
    MIDI.begin(MIDI_CHANNEL_OMNI);
#endif
}

std::vector<arduino::digital::Pin> initPins()
{
    std::vector<arduino::digital::Pin> pins;
    for (uint8_t pinNumber = 0; pinNumber < arduino::digital::numberOfPins; ++pinNumber)
    {
        pins.push_back(arduino::digital::Pin{pinNumber});
    }

    return pins;
}

kbd::KeyboardMatricesIO initKeyboardMatrices(std::vector<arduino::digital::Pin> &pins)
{
    // See the circuit diagram for details regarding inputs/outputs configuration.
    return kbd::KeyboardMatricesIO{{kbd::KeyboardMatrixIO::Builder{
                                        .firstClosedContactsOutputs{50, 46, 42, 38, 37, 32},
                                        .lastClosedContactsOutputs{52, 48, 44, 40, 36, 34},
                                        .inputs{53, 51, 49, 47, 45, 43, 41, 39},
                                        .numberOfKeysBeingScanned{48},
                                        .pins{pins}}
                                        .build(),
                                    kbd::KeyboardMatrixIO::Builder{
                                        .firstClosedContactsOutputs{28, 24, 2, 6, 5},
                                        .lastClosedContactsOutputs{30, 26, 22, 4, 7},
                                        .inputs{35, 33, 31, 29, 27, 25, 23, 3},
                                        .numberOfKeysBeingScanned{40},
                                        .pins{pins}}
                                        .build()}};
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

#ifdef AVR_STUB_DEBUG
    debug_init();
#endif

    attachUsbDeviceIfAny();

    initMidiInterface();

    auto pins{initPins()};

    auto keyboardMatrices{initKeyboardMatrices(pins)};

    auto keyboardController{kbd::KeyboardController::Builder{.firstKeyMidiNoteNumber{21},
                                                             .midiChannel{1},
                                                             .keyboardMatrices{keyboardMatrices},
                                                             .midiInterface{MIDI}}
                                .build()};

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

    serialEventSafeRun();
}
