#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController(const uint8_t firstKeyMidiNoteNumber,
                                           const uint8_t midiChannel,
                                           PedalsIO &pedalsIO,
                                           KeyboardMatricesIO &keyboardMatrices,
                                           MidiInterface &midiInterface) : firstKeyMidiNoteNumber{firstKeyMidiNoteNumber},
                                                                           midiChannel{midiChannel},
                                                                           pedalsIO{pedalsIO},
                                                                           keyboardMatrices{keyboardMatrices},
                                                                           midiInterface{midiInterface}

    {
        this->pedals.push_back(Pedal{0, Pedal::Function::soft});
        this->pedals.push_back(Pedal{1, Pedal::Function::sostenuto});
        this->pedals.push_back(Pedal{2, Pedal::Function::sustain});
        
        for (uint8_t keyNumber{0}; keyNumber < keyboardMatrices.getNumberOfKeysBeingScanned(); ++keyNumber)
        {
            this->keys.push_back(Key{keyNumber});
        }
    }

    void KeyboardController::sendMidiEvents()
    {
        for (auto &pedal : this->pedals)
        {
            pedal.sendMidiEvent(this->midiChannel,
                                this->midiInterface,
                                this->pedalsIO);
        }

        for (auto &key : this->keys)
        {
            key.sendMidiEvent(this->firstKeyMidiNoteNumber,
                              this->midiChannel,
                              this->midiInterface,
                              this->keyboardMatrices);
        }
    }
}