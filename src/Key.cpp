#include "Key.hpp"

namespace kbd
{
    Key::Key(const uint8_t number, MidiInterface *const midiInterface) : contacts{ContactPair{number}},
                                                                         midiInterface{midiInterface}
    {
    }

    void Key::sendMidiEvent()
    {
        this->contacts.updateStateWithDebouncing();

        updateActualState();

        if (this->previousState != this->actualState)
        {
            const uint8_t noteNumber = this->contacts.number + firstKeyMidiNoteNumber;

            if (this->actualState == State::depressed)
            {
                this->midiInterface->sendNoteOn(noteNumber, this->velocity, midiChannel);
            }
            else if (this->actualState == State::released)
            {
                this->midiInterface->sendNoteOff(noteNumber, this->velocity, midiChannel);
            }

            this->previousState = this->actualState;
        }
    }

    void Key::updateActualState()
    {
        const auto firstContact{this->contacts.firstClosed};
        const auto lastContact{this->contacts.lastClosed};

        if (firstContact.isClosed() && lastContact.isClosed())
        {
            this->actualState = State::depressed;
            if (this->previousState == State::halfReleased)
            {
                //Moving a key from the half-released state to the depressed state may be considered as a repetition
                //that can be performed on grand pianos.
                //Previously calculated velocity shouldn't be changed in case of repetition.
            }
            else
            {
                this->velocity =
                    lastContact.getLastTimeStateChangedMillis() - firstContact.getLastTimeStateChangedMillis(); //TODO normalization
            }
        }

        if (firstContact.isClosed() && !lastContact.isClosed() && this->previousState == State::depressed)
        {
            this->actualState = State::halfReleased;
        }

        if (!firstContact.isClosed() && !lastContact.isClosed())
        {
            this->actualState = State::released;
            this->velocity =
                firstContact.getLastTimeStateChangedMillis() - lastContact.getLastTimeStateChangedMillis(); //TODO normalization
        }
    }
}