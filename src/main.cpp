#include <map>
#include <vector>

#include <stdint.h>

#include <Arduino.h>
#include <MIDI.h>

#ifdef AVR_STUB_DEBUG
#include <avr8-stub.h>
#endif

#include "KeyboardMatricesIO.hpp"
#include "KeyboardController.hpp"
#include "DigitalIO.hpp"
#include "PedalsIO.hpp"
#include "Pedal.hpp"

using namespace kbd;
using namespace arduino::digital;

void initAvrStubDebug();
void attachUsbDevice();
KeyboardMatricesIO initKeyboardMatricesIO(const Pins &);
void sendMidiEvents(KeyboardController &);
void serialEventSafeRun();

int main()
{
    init();
    initAvrStubDebug();
    attachUsbDevice();

// For some reason this cannot be extracted to a function returning MIDI. This works either globally or right here in main().
#ifdef AVR_STUB_DEBUG
    MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI)
#else
    MIDI_CREATE_DEFAULT_INSTANCE()
    MIDI.begin(MIDI_CHANNEL_OMNI);
#endif

    const Pins pins{{{Mode::output, {50, 52, 46, 48, 42, 44, 38, 40, 37, 36, 32, 34, 28, 30, 24, 26, 2, 22, 6, 4, 5, 7}},
                     {Mode::inputWithInternalPullUp, {53, 51, 49, 47, 45, 43, 41, 39, 35, 33, 31, 29, 27, 25, 23, 3, 8, 9, 10}}}};
    const PedalsIO pedalsIO{{{Pedal::Function::soft, pins[8]},
                             {Pedal::Function::sostenuto, pins[9]},
                             {Pedal::Function::sustain, pins[10]}}};
    const auto keyboardMatricesIO{initKeyboardMatricesIO(pins)};
    KeyboardController controller{pedalsIO, keyboardMatricesIO, MIDI};    

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

KeyboardMatricesIO initKeyboardMatricesIO(const Pins &pins)
{
    return KeyboardMatricesIO{{KeyboardMatrixIO::Builder{
                                   .outputs{{.firstActuatedContactOutput{pins[50]}, .lastActuatedContactOutput{pins[52]}},
                                            {.firstActuatedContactOutput{pins[46]}, .lastActuatedContactOutput{pins[48]}},
                                            {.firstActuatedContactOutput{pins[42]}, .lastActuatedContactOutput{pins[44]}},
                                            {.firstActuatedContactOutput{pins[38]}, .lastActuatedContactOutput{pins[40]}},
                                            {.firstActuatedContactOutput{pins[37]}, .lastActuatedContactOutput{pins[36]}},
                                            {.firstActuatedContactOutput{pins[32]}, .lastActuatedContactOutput{pins[34]}}},
                                   .inputs{{pins[53], pins[51], pins[49], pins[47], pins[45], pins[43], pins[41], pins[39]}}}
                                   .build(),
                               KeyboardMatrixIO::Builder{
                                   .outputs{{.firstActuatedContactOutput{pins[28]}, .lastActuatedContactOutput{pins[30]}},
                                            {.firstActuatedContactOutput{pins[24]}, .lastActuatedContactOutput{pins[26]}},
                                            {.firstActuatedContactOutput{pins[2]}, .lastActuatedContactOutput{pins[22]}},
                                            {.firstActuatedContactOutput{pins[6]}, .lastActuatedContactOutput{pins[4]}},
                                            {.firstActuatedContactOutput{pins[5]}, .lastActuatedContactOutput{pins[7]}}},
                                   .inputs{{pins[35], pins[33], pins[31], pins[29], pins[27], pins[25], pins[23], pins[3]}}}
                                   .build()}};
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
