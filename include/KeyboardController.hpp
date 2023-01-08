#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>
#include <utility>

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
    using uint8_tPair = std::pair<uint8_t, uint8_t>;

    class KeyboardController
    {
    public:
        KeyboardController();

        void sendMidiEvents();

        static inline constexpr uint8_t midiChannel{1};

    private:
        static inline constexpr uint8_t firstKeyMidiNoteNumber{21};

        static std::vector<KeyGroupOutputs> initKeyGroupsOutputs(const std::vector<uint8_tPair> &pinsNumbers);
        static std::vector<Pin> initInputs(const std::vector<uint8_t> &pinsNumbers);

        static inline const IOMatrices ioMatrices{
            {IOMatrix{{KeyboardController::initKeyGroupsOutputs({uint8_tPair{50, 52},
                                                                 uint8_tPair{46, 48},
                                                                 uint8_tPair{42, 44},
                                                                 uint8_tPair{38, 40},
                                                                 uint8_tPair{37, 36},
                                                                 uint8_tPair{32, 34}})},
                      {KeyboardController::initInputs({53, 51, 49, 47, 45, 43, 41, 39})}},
             IOMatrix{{KeyboardController::initKeyGroupsOutputs({uint8_tPair{28, 30},
                                                                 uint8_tPair{24, 26},
                                                                 uint8_tPair{2, 22},
                                                                 uint8_tPair{6, 4},
                                                                 uint8_tPair{5, 7}})},
                      {KeyboardController::initInputs({35, 33, 31, 29, 27, 25, 23, 3})}}}};

        std::vector<Pedal> pedals{Pedal{Pedal::Function::soft, Pin{8, Mode::inputWithInternalPullUp}},
                                  Pedal{Pedal::Function::sostenuto, Pin{9, Mode::inputWithInternalPullUp}},
                                  Pedal{Pedal::Function::sustain, Pin{10, Mode::inputWithInternalPullUp}}};

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