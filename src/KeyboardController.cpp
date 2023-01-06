#include "KeyboardController.hpp"

namespace kbd
{
    KeyboardController::KeyboardController(const PedalsIO &pedalsIO,
                                           const arduino::digital::IOMatrices &ioMatrices,
                                           MidiInterface &midiInterface) : pedalsIO{pedalsIO},
                                                                           ioMatrices{ioMatrices},
                                                                           midiInterface{midiInterface},
                                                                           keys{std::vector<Key>{ioMatrices.getNumberOfKeysBeingScanned()}}

    {
    }

    void KeyboardController::sendMidiEvents()
    {
        for (auto &pedal : this->pedals)
        {
            pedal.sendMidiEvent(this->midiChannel,
                                this->midiInterface,
                                this->pedalsIO);
        }

        const auto keysInputsStates{this->ioMatrices.getActualInstantaneousKeysInputsStates()};

        for (uint8_t keyNumber{0}; keyNumber < ioMatrices.getNumberOfKeysBeingScanned(); ++keyNumber)
        {
            this->keys[keyNumber].sendMidiEvent(this->firstKeyMidiNoteNumber + keyNumber,
                                                this->midiChannel,
                                                this->midiInterface,
                                                keysInputsStates[keyNumber]);
        }
    }
}