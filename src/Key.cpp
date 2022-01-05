#include "Key.hpp"

namespace kbd
{
    Key::Key(const uint8_t number) : number{number}
    {
    }

    void Key::sendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                            const uint8_t midiChannel,
                            MidiInterface &midiInterface)
    {
        this->contacts.updateStateWithDebouncing(this->number);

        updateActualState();

        if (this->previousState == this->actualState)
        {
            //Do nothing.
        }
        else
        {
            const uint8_t noteNumber = this->number + firstKeyMidiNoteNumber;

            switch (this->actualState)
            {
            case State::depressed:
                midiInterface.sendNoteOn(noteNumber, this->velocity, midiChannel);
                this->previousState = this->actualState;
                break;
            case State::released:
                midiInterface.sendNoteOff(noteNumber, this->velocity, midiChannel);
                this->previousState = this->actualState;
                break;
            case State::halfReleased:
                //Do nothing.
                break;
            default:
                break;
            }
        }
    }

    void Key::updateActualState()
    {
        if (this->contacts.isAsKeyDepressed())
        {
            this->actualState = State::depressed;
            if (this->previousState == State::halfReleased)
            {
                //Moving a key from the half-released state to the depressed state may be treated as a repetition
                //that can be performed on grand pianos and some upright pianos.
                //Previously calculated velocity shouldn't be changed in case of repetition.
            }
            else
            {
                this->velocity = this->contacts.getPressingTimeMillis(); //TODO normalization
            }
        }
        else if (this->contacts.isAsKeyHalfReleased())
        {
            if (this->previousState == State::depressed)
            {
                //Preparing a key for repetition.
                this->actualState = State::halfReleased;
            }
            else
            {
                //Do nothing.
            }
        }
        else if (this->contacts.isAsKeyReleases())
        {
            this->actualState = State::released;
            this->velocity = this->contacts.getReleasingTimeMillis(); //TODO normalization
        }
    }
}