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
            if (this->velocity == 0)
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
                    break;
                case State::released:
                    midiInterface.sendNoteOff(noteNumber, this->velocity, midiChannel);                    
                    break;
                case State::halfReleased:
                    //Do nothing.
                    break;
                default:
                    break;
                }
            }

            this->previousState = this->actualState;
        }
    }

    void Key::updateActualState()
    {
        if (this->contacts.isAsKeyIsDepressed())
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
                const auto pressingTimeMillis{this->contacts.getPressingTimeMillis()};
                if (pressingTimeMillis <= maxManipulationTimeMillis)
                {
                    this->velocity = pressingTimeMillis; //TODO normalization
                }
                else
                {
                    this->velocity = 0;
                }
            }
        }
        else if (this->contacts.isAsKeyIsHalfReleased())
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
        else if (this->contacts.isAsKeyIsReleased())
        {
            this->actualState = State::released;
            const auto releasingTimeMillis{this->contacts.getReleasingTimeMillis()};
            if (releasingTimeMillis <= maxManipulationTimeMillis)
            {
                this->velocity = releasingTimeMillis; //TODO normalization
            }
            else
            {
                this->velocity = 0;
            }
        }
    }
}