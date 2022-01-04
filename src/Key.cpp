#include "Key.hpp"

namespace kbd
{
    Key::Key(const uint8_t number) : contacts{ContactPair{number}}
    {
    }

    void Key::sendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                            const uint8_t midiChannel,
                            MidiInterface *const midiInterface)
    {
        this->contacts.updateStateWithDebouncing();

        updateActualState();

        if (this->previousState == this->actualState)
        {
            //Do nothing.
        }
        else
        {
            const uint8_t noteNumber = this->contacts.number + firstKeyMidiNoteNumber;

            switch (this->actualState)
            {
            case State::depressed:
                midiInterface->sendNoteOn(noteNumber, this->velocity, midiChannel);
                this->previousState = this->actualState;
                break;
            case State::released:
                midiInterface->sendNoteOff(noteNumber, this->velocity, midiChannel);
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
        const auto firstContact{this->contacts.firstClosed};
        const auto lastContact{this->contacts.lastClosed};

        if (firstContact.isClosed() && lastContact.isClosed())
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
                this->velocity =
                    lastContact.getLastTimeStateChangedMillis() - firstContact.getLastTimeStateChangedMillis(); //TODO normalization
            }
        }
        else if (firstContact.isClosed() && !lastContact.isClosed())
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
        else if (!firstContact.isClosed() && !lastContact.isClosed())
        {
            this->actualState = State::released;
            this->velocity =
                firstContact.getLastTimeStateChangedMillis() - lastContact.getLastTimeStateChangedMillis(); //TODO normalization
        }
        else if (!firstContact.isClosed() && lastContact.isClosed())
        {
            //The state is illegal and shouldn't be processed.
        }
    }
}