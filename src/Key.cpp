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
            doSendMidiEvent(firstKeyMidiNoteNumber, midiChannel, midiInterface);
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
                    this->velocity = slope * pressingTimeMillis + maxVelocity;
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
                this->velocity = slope * releasingTimeMillis + maxVelocity;
            }
            else
            {
                this->velocity = 0;
            }
        }
    }

    void Key::doSendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                                 const uint8_t midiChannel,
                                 MidiInterface &midiInterface)
    {
        const uint8_t noteNumber = this->number + firstKeyMidiNoteNumber;

        switch (this->actualState)
        {
        case State::depressed:
            if (this->velocity == 0)
            {
                //Do nothing.
            }
            else
            {
                midiInterface.sendNoteOn(noteNumber, this->velocity, midiChannel);
            }
            this->previousState = this->actualState;
            break;
        case State::released:
            if (this->velocity == 0)
            {
                //Do nothing.
            }
            else
            {
                midiInterface.sendNoteOff(noteNumber, this->velocity, midiChannel);
            }
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