#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <MIDI.h>

#include "Key.hpp"
#include "Pedal.hpp"
#include "Contact.hpp"
#include "KeyContacts.hpp"
#include "IOMatrices.hpp"
#include "PedalsIO.hpp"

namespace kbd
{
    using MidiInterface = midi::MidiInterface<midi::SerialMIDI<HardwareSerial>>;

    class KeyboardController
    {
    public:
        KeyboardController(const PedalsIO &,
                           const arduino::digital::IOMatrices &,
                           MidiInterface &);

        void sendMidiEvents();

    private:
        static inline constexpr uint8_t firstKeyMidiNoteNumber{21};
        static inline constexpr uint8_t midiChannel{1};
        const PedalsIO &pedalsIO;
        const arduino::digital::IOMatrices &ioMatrices;
        MidiInterface &midiInterface;

        std::vector<Pedal> pedals{Pedal{Pedal::Function::soft},
                                  Pedal{Pedal::Function::sostenuto},
                                  Pedal{Pedal::Function::sustain}};
        std::vector<Contact> pedalsContacts{this->pedals.size()};

        std::vector<Key> keys;

        void updateKeysContactsState(const std::vector<KeyInputStates> &);
    };

}

#endif