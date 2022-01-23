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
using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

void initAvrStubDebug();
void attachUsbDevice();
kbd::KeyboardMatricesIO initKeyboardMatrices();
kbd::KeyboardController initKeyboardController(kbd::KeyboardMatricesIO &, MidiInterface &);
std::vector<Pin> initOutputsWithState(const std::vector<uint8_t>, const State);
std::vector<Pin> initInputsPulledUp(const std::vector<uint8_t>);
void sendMidiEvents(const kbd::KeyboardController);
void serialEventSafeRun();

int main()
{
    init();
    initAvrStubDebug();
    attachUsbDevice();

//For some reason this cannot be extracted to a function returning MIDI. This works either globally or right here in main().
#ifdef AVR_STUB_DEBUG
    MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI)
#else
    MIDI_CREATE_DEFAULT_INSTANCE()
    MIDI.begin(MIDI_CHANNEL_OMNI);
#endif

    auto keyboardMatrices{initKeyboardMatrices()};

    sendMidiEvents(initKeyboardController(keyboardMatrices, MIDI));
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

kbd::KeyboardMatricesIO initKeyboardMatrices()
{
    return kbd::KeyboardMatricesIO{{kbd::KeyboardMatrixIO::Builder{
                                        .firstClosedContactsOutputs{initOutputsWithState({50, 46, 42, 38, 37, 32}, State::high)},
                                        .lastClosedContactsOutputs{initOutputsWithState({52, 48, 44, 40, 36, 34}, State::high)},
                                        .inputs{initInputsPulledUp({53, 51, 49, 47, 45, 43, 41, 39})},
                                        .numberOfKeysBeingScanned{48}}
                                        .build(),
                                    kbd::KeyboardMatrixIO::Builder{
                                        .firstClosedContactsOutputs{initOutputsWithState({28, 24, 2, 6, 5}, State::high)},
                                        .lastClosedContactsOutputs{initOutputsWithState({30, 26, 22, 4, 7}, State::high)},
                                        .inputs{initInputsPulledUp({35, 33, 31, 29, 27, 25, 23, 3})},
                                        .numberOfKeysBeingScanned{40}}
                                        .build()}};
}

kbd::KeyboardController initKeyboardController(kbd::KeyboardMatricesIO &keyboardMatrices, MidiInterface &midiInterface)
{
    return kbd::KeyboardController::Builder{.firstKeyMidiNoteNumber{21},
                                            .midiChannel{1},
                                            .keyboardMatrices{keyboardMatrices},
                                            .midiInterface{midiInterface}}
        .build();
}

std::vector<Pin> initOutputsWithState(const std::vector<uint8_t> pinNumbers, const State state)
{
    std::vector<Pin> pins;
    for (const uint8_t pinNumber : pinNumbers)
    {
        const Pin pin{pinNumber};
        pin.setMode(Mode::output);
        pin.setState(state);
        pins.push_back(pin);
    }

    return pins;
}

std::vector<Pin> initInputsPulledUp(const std::vector<uint8_t> pinNumbers)
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
