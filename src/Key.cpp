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
        else if (this->contacts.isAsKeyIsReleased())
        {
            this->actualState = State::released;
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
            midiInterface.sendNoteOn(noteNumber, this->velocity, midiChannel);

#ifdef DEBUG_MESSAGES
            char buffer[10];
            Serial.write("ON: note=");
            Serial.write(itoa(noteNumber, buffer, 10));
            Serial.write(", vel=");
            Serial.write(itoa(this->velocity, buffer, 10));
            Serial.write(", time=");
            Serial.write(ltoa(this->contacts.getPressingTimeMillis(), buffer, 10));
            Serial.write("\n");
#endif

            this->previousState = this->actualState;
            break;
        case State::released:
            midiInterface.sendNoteOff(noteNumber, defaultVelocity, midiChannel);

#ifdef DEBUG_MESSAGES
            Serial.write("OFF: note=");
            Serial.write(itoa(noteNumber, buffer, 10));
            Serial.write(", time=");
            Serial.write(ltoa(this->contacts.getReleasingTimeMillis(), buffer, 10));
            Serial.write("\n");
#endif

            this->previousState = this->actualState;
            break;
        default:
            break;
        }
    }
}