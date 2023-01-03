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

using Pin = arduino::digital::Pin;
using PinMap = arduino::digital::PinMap;
using State = arduino::digital::State;
using Mode = arduino::digital::Mode;
using KeyGroupOutputs = arduino::digital::KeyGroupOutputs;
using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

void initAvrStubDebug();
void attachUsbDevice();
PinMap initPins(const std::map<Mode, std::vector<uint8_t>> &);
kbd::PedalsIO initPedals(const PinMap &);
kbd::KeyboardMatricesIO initKeyboardMatrices(const PinMap &);
kbd::KeyboardController initKeyboardController(kbd::PedalsIO &, kbd::KeyboardMatricesIO &, MidiInterface &);
void sendMidiEvents(const kbd::KeyboardController);
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

    auto pins{initPins({{Mode::output, {50, 52, 46, 48, 42, 44, 38, 40, 37, 36, 32, 34, 28, 30, 24, 26, 2, 22, 6, 4, 5, 7}},
                        {Mode::inputWithInternalPullUp, {53, 51, 49, 47, 45, 43, 41, 39, 35, 33, 31, 29, 27, 25, 23, 3, 8, 9, 10}}})};
    auto pedalsIO{initPedals(pins)};
    auto keyboardMatrices{initKeyboardMatrices(pins)};

    sendMidiEvents(initKeyboardController(pedalsIO, keyboardMatrices, MIDI));
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

PinMap initPins(const std::map<Mode, std::vector<uint8_t>> &modeToPinMapping)
{
    PinMap pins;

    for (const auto &[mode, pinNumbers] : modeToPinMapping)
    {
        for (const uint8_t pinNumber : pinNumbers)
        {
            const Pin pin{pinNumber};
            pin.setMode(mode);

            if (mode == Mode::output)
            {
                pin.setState(State::high);
            }

            pins.insert(pinNumber, pin);
        }
    }

    return pins;
}

kbd::PedalsIO initPedals(const PinMap &pins)
{
    return kbd::PedalsIO{{pins[8], pins[9], pins[10]}};
}

kbd::KeyboardMatricesIO initKeyboardMatrices(const PinMap &pins)
{
    return kbd::KeyboardMatricesIO{{kbd::KeyboardMatrixIO::Builder{
                                        .outputs{{.firstActuatedContactOutput{pins[50]}, .lastActuatedContactOutput{pins[52]}},
                                                 {.firstActuatedContactOutput{pins[46]}, .lastActuatedContactOutput{pins[48]}},
                                                 {.firstActuatedContactOutput{pins[42]}, .lastActuatedContactOutput{pins[44]}},
                                                 {.firstActuatedContactOutput{pins[38]}, .lastActuatedContactOutput{pins[40]}},
                                                 {.firstActuatedContactOutput{pins[37]}, .lastActuatedContactOutput{pins[36]}},
                                                 {.firstActuatedContactOutput{pins[32]}, .lastActuatedContactOutput{pins[34]}}},
                                        .inputs{{pins[53], pins[51], pins[49], pins[47], pins[45], pins[43], pins[41], pins[39]}}}
                                        .build(),
                                    kbd::KeyboardMatrixIO::Builder{
                                        .outputs{{.firstActuatedContactOutput{pins[28]}, .lastActuatedContactOutput{pins[30]}},
                                                 {.firstActuatedContactOutput{pins[24]}, .lastActuatedContactOutput{pins[26]}},
                                                 {.firstActuatedContactOutput{pins[2]}, .lastActuatedContactOutput{pins[22]}},
                                                 {.firstActuatedContactOutput{pins[6]}, .lastActuatedContactOutput{pins[4]}},
                                                 {.firstActuatedContactOutput{pins[5]}, .lastActuatedContactOutput{pins[7]}}},
                                        .inputs{{pins[35], pins[33], pins[31], pins[29], pins[27], pins[25], pins[23], pins[3]}}}
                                        .build()}};
}

kbd::KeyboardController initKeyboardController(kbd::PedalsIO &pedalsIO,
                                               kbd::KeyboardMatricesIO &keyboardMatrices,
                                               MidiInterface &midiInterface)
{
    return kbd::KeyboardController::Builder{.firstKeyMidiNoteNumber{21},
                                            .midiChannel{1},
                                            .pedalsIO{pedalsIO},
                                            .keyboardMatrices{keyboardMatrices},
                                            .midiInterface{midiInterface}}
        .build();
}

void sendMidiEvents(kbd::KeyboardController keyboardController)
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
