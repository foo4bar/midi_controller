#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <stdint.h>

#include <MIDI.h>
#include <HardwareSerial.h>

#include "Key.hpp"
#include "IOMatrices.hpp"
#include "IOMatrix.hpp"
#include "Pedal.hpp"
#include "DigitalIO.hpp"

namespace kbd
{
    using namespace arduino::digital;
    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class KeyboardController
    {
    public:
        KeyboardController();

        void sendMidiEvents();

        static inline constexpr uint8_t midiChannel{1};

    private:
        static inline constexpr uint8_t firstKeyMidiNoteNumber{21};

        static inline const Pins pins{
            {{Mode::output, {50, 52, 46, 48, 42, 44, 38, 40, 37, 36, 32, 34, 28, 30, 24, 26, 2, 22, 6, 4, 5, 7}},
             {Mode::inputWithInternalPullUp, {53, 51, 49, 47, 45, 43, 41, 39, 35, 33, 31, 29, 27, 25, 23, 3, 8, 9, 10}}}};

        static inline const IOMatrices ioMatrices{
            {IOMatrix::Builder{
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

        std::vector<Pedal> pedals{Pedal{Pedal::Function::soft, pins[8]},
                                  Pedal{Pedal::Function::sostenuto, pins[9]},
                                  Pedal{Pedal::Function::sustain, pins[10]}};

        std::vector<Key> keys{std::vector<Key>{KeyboardController::ioMatrices.getNumberOfKeysBeingScanned()}};

#ifdef AVR_STUB_DEBUG
        midi::SerialMIDI<HardwareSerial> serialMidi{Serial1};
#else
        midi::SerialMIDI<HardwareSerial> serialMidi{Serial};
#endif

        MidiInterface midiInterface{this->serialMidi};
    };
}

#endif