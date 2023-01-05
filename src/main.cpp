
#include <MIDI.h>

#ifdef CYCLE_TIME_DEBUG_MESSAGES
#include <Arduino.h>
#endif

#ifdef AVR_STUB_DEBUG
#include <avr8-stub.h>
#endif

#include "IOMatrices.hpp"
#include "KeyboardController.hpp"
#include "DigitalIO.hpp"
#include "PedalsIO.hpp"
#include "Pedal.hpp"

using namespace kbd;
using namespace arduino::digital;

using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

void initAvrStubDebug();
void attachUsbDevice();
IOMatrices initIOMatrices(const Pins &);
MidiInterface initMidiInterface();
MidiInterface createMidiInterface(HardwareSerial &);
void sendMidiEvents(KeyboardController &);
void serialEventSafeRun();

int main()
{
    init();
    initAvrStubDebug();
    attachUsbDevice();

    const Pins pins{{{Mode::output, {50, 52, 46, 48, 42, 44, 38, 40, 37, 36, 32, 34, 28, 30, 24, 26, 2, 22, 6, 4, 5, 7}},
                     {Mode::inputWithInternalPullUp, {53, 51, 49, 47, 45, 43, 41, 39, 35, 33, 31, 29, 27, 25, 23, 3, 8, 9, 10}}}};
    const PedalsIO pedalsIO{{{Pedal::Function::soft, pins[8]},
                             {Pedal::Function::sostenuto, pins[9]},
                             {Pedal::Function::sustain, pins[10]}}};
    const auto ioMatrices{initIOMatrices(pins)};
    auto midiInterface{initMidiInterface()};
    KeyboardController controller{pedalsIO, ioMatrices, midiInterface};

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

IOMatrices initIOMatrices(const Pins &pins)
{
    return IOMatrices{{IOMatrix::Builder{
                           .keyGroupsOutputs{{.firstActuatedKeysContactsOutput{pins[50]}, .lastActuatedKeysContactsOutput{pins[52]}},
                                             {.firstActuatedKeysContactsOutput{pins[46]}, .lastActuatedKeysContactsOutput{pins[48]}},
                                             {.firstActuatedKeysContactsOutput{pins[42]}, .lastActuatedKeysContactsOutput{pins[44]}},
                                             {.firstActuatedKeysContactsOutput{pins[38]}, .lastActuatedKeysContactsOutput{pins[40]}},
                                             {.firstActuatedKeysContactsOutput{pins[37]}, .lastActuatedKeysContactsOutput{pins[36]}},
                                             {.firstActuatedKeysContactsOutput{pins[32]}, .lastActuatedKeysContactsOutput{pins[34]}}},
                           .keysInputs{{pins[53], pins[51], pins[49], pins[47], pins[45], pins[43], pins[41], pins[39]}}}
                           .build(),
                       IOMatrix::Builder{
                           .keyGroupsOutputs{{.firstActuatedKeysContactsOutput{pins[28]}, .lastActuatedKeysContactsOutput{pins[30]}},
                                             {.firstActuatedKeysContactsOutput{pins[24]}, .lastActuatedKeysContactsOutput{pins[26]}},
                                             {.firstActuatedKeysContactsOutput{pins[2]}, .lastActuatedKeysContactsOutput{pins[22]}},
                                             {.firstActuatedKeysContactsOutput{pins[6]}, .lastActuatedKeysContactsOutput{pins[4]}},
                                             {.firstActuatedKeysContactsOutput{pins[5]}, .lastActuatedKeysContactsOutput{pins[7]}}},
                           .keysInputs{{pins[35], pins[33], pins[31], pins[29], pins[27], pins[25], pins[23], pins[3]}}}
                           .build()}};
}

MidiInterface initMidiInterface()
{
#ifdef AVR_STUB_DEBUG
    auto midiInterface{createMidiInterface(Serial1)};
#else
    auto midiInterface{createMidiInterface(Serial)};
    midiInterface.begin(MIDI_CHANNEL_OMNI);
#endif

    return midiInterface;
}

MidiInterface createMidiInterface(HardwareSerial &hardwareSerial)
{
    static midi::SerialMIDI<HardwareSerial> serialMidi{hardwareSerial}; // It's used _by_reference_ by the MidiInterface 
                                                                        // instance created below.
                                                                        // Thus, it has to be static to be not destroyed.

    return MidiInterface{serialMidi};
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
