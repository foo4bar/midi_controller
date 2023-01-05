#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController(const PedalsIO &pedalsIO,
                                           const IOMatrices &ioMatrices,
                                           MidiInterface &midiInterface) : pedalsIO{pedalsIO},
                                                                           ioMatrices{ioMatrices},
                                                                           midiInterface{midiInterface}

    {
        for (uint8_t keyNumber{0}; keyNumber < ioMatrices.getNumberOfKeysBeingScanned(); ++keyNumber)
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
                              this->ioMatrices);
        }
    }
}