#include "Key.hpp"

namespace kbd
{
    Key::Key(const uint8_t number) : contacts{ContactPair{number}}
    {
    }

    void Key::sendMidiEvent()
    {
        this->contacts.updateStateWithDebouncing();

        //TODO calculate key state based on contacts state

        if (this->previousState != this->actualState)
        {
            const uint8_t noteNumber{midictrl::Midi::getActualMidiNoteNumber(this->contacts.number)};

            if (this->actualState == State::depressed)
            {
                midictrl::Midi::getIstance()
                    .sendNoteOn(noteNumber, this->velocity);
            }
            else if (this->actualState == State::released)
            {
                midictrl::Midi::getIstance()
                    .sendNoteOff(noteNumber, this->velocity);
            }

            this->previousState = this->actualState;
        }
    }
}