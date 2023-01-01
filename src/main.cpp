#include <Arduino.h>
#include <MIDI.h>

#ifdef AVR_STUB_DEBUG
#include <avr8-stub.h>
#endif

#include "KeyboardMatricesIO.hpp"
#include "KeyboardController.hpp"
#include "DigitalIO.hpp"

using Pin = arduino::digital::Pin;
using State = arduino::digital::State;
using Mode = arduino::digital::Mode;
using KeyGroupOutputs = arduino::digital::KeyGroupOutputs;
using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

void initAvrStubDebug();
void attachUsbDevice();
kbd::PedalsIO initPedals();
kbd::KeyboardMatricesIO initKeyboardMatrices();
kbd::KeyboardController initKeyboardController(kbd::PedalsIO &, kbd::KeyboardMatricesIO &, MidiInterface &);
Pin initOutputWithState(const uint8_t pinNumber, const State state);
std::vector<Pin> initInputsPulledUp(const std::vector<uint8_t> &);
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

    auto pedalsIO{initPedals()};
    auto keyboardMatrices{initKeyboardMatrices()};

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

kbd::PedalsIO initPedals()
{
    return kbd::PedalsIO{initInputsPulledUp({8, 9, 10})};
}

kbd::KeyboardMatricesIO initKeyboardMatrices()
{
    auto keyGroupOutputs0{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(50, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(52, State::high)}}
                              .build()};
    auto keyGroupOutputs1{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(46, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(48, State::high)}}
                              .build()};
    auto keyGroupOutputs2{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(42, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(44, State::high)}}
                              .build()};
    auto keyGroupOutputs3{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(38, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(40, State::high)}}
                              .build()};
    auto keyGroupOutputs4{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(37, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(36, State::high)}}
                              .build()};
    auto keyGroupOutputs5{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(32, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(34, State::high)}}
                              .build()};
    auto keyGroupOutputs6{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(28, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(30, State::high)}}
                              .build()};
    auto keyGroupOutputs7{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(24, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(26, State::high)}}
                              .build()};
    auto keyGroupOutputs8{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(2, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(22, State::high)}}
                              .build()};
    auto keyGroupOutputs9{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(6, State::high)},
                                                   .lastActuatedContactOutput{initOutputWithState(4, State::high)}}
                              .build()};
    auto keyGroupOutputs10{KeyGroupOutputs::Builder{.firstActuatedContactOutput{initOutputWithState(5, State::high)},
                                                    .lastActuatedContactOutput{initOutputWithState(7, State::high)}}
                               .build()};

    return kbd::KeyboardMatricesIO{{kbd::KeyboardMatrixIO::Builder{.outputs{keyGroupOutputs0,
                                                                            keyGroupOutputs1,
                                                                            keyGroupOutputs2,
                                                                            keyGroupOutputs3,
                                                                            keyGroupOutputs4,
                                                                            keyGroupOutputs5},
                                                                   .inputs{initInputsPulledUp({53, 51, 49, 47, 45, 43, 41, 39})}}
                                        .build(),
                                    kbd::KeyboardMatrixIO::Builder{.outputs{keyGroupOutputs6,
                                                                            keyGroupOutputs7,
                                                                            keyGroupOutputs8,
                                                                            keyGroupOutputs9,
                                                                            keyGroupOutputs10},
                                                                   .inputs{initInputsPulledUp({35, 33, 31, 29, 27, 25, 23, 3})}}
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

Pin initOutputWithState(const uint8_t pinNumber, const State state)
{
    const Pin pin{pinNumber};
    pin.setMode(Mode::output);
    pin.setState(state);

    return pin;
}

std::vector<Pin> initInputsPulledUp(const std::vector<uint8_t> &pinNumbers)
{
    std::vector<Pin> pins;
    for (const uint8_t pinNumber : pinNumbers)
    {
        const Pin pin{pinNumber};
        pin.setMode(Mode::inputWithInternalPullUp);
        pins.push_back(pin);
    }

    return pins;
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
