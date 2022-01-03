#include "Key.hpp"

namespace kbd
{
    Key::Key(const uint8_t number,
             void (*sendNoteOn)(const uint8_t, const uint8_t),
             void (*sendNoteOff)(const uint8_t, const uint8_t),
             uint8_t (*getActualMidiNoteNumber)(const uint8_t)) : contacts{ContactPair{number}},
                                                                  sendNoteOn{sendNoteOn},
                                                                  sendNoteOff{sendNoteOff},
                                                                  getActualMidiNoteNumber{getActualMidiNoteNumber}
    {
    }

    void Key::sendMidiEvent()
    {
        this->contacts.updateStateWithDebouncing();

        // TODO calculate key state based on contacts state

        if (this->previousState != this->actualState)
        {
            const uint8_t noteNumber{getActualMidiNoteNumber(this->contacts.number)};

            if (this->actualState == State::depressed)
            {
                sendNoteOn(noteNumber, this->velocity);
            }
            else if (this->actualState == State::released)
            {
                sendNoteOff(noteNumber, this->velocity);
            }

            this->previousState = this->actualState;
        }
    }
}