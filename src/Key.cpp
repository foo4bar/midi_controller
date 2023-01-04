#include "Key.hpp"

namespace kbd
{
    Key::Key(const uint8_t number) : number{number}, contacts{KeyContacts{number}}
    {
    }

    void Key::sendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                            const uint8_t midiChannel,
                            MidiInterface &midiInterface,
                            const KeyboardMatricesIO &keyboardMatricesIO)
    {
        this->contacts.updateStateWithDebouncing(keyboardMatricesIO);

        const State actualState{getActualState()};

        if (actualState == State::moving || this->previousState == actualState)
        {
            //Do nothing.
        }
        else
        {
#if !defined(AVR_STUB_DEBUG) && !defined(CONTACT_EVENTS_DEBUG_MESSAGES)
            doSendMidiEvent(firstKeyMidiNoteNumber,
                            midiChannel,
                            midiInterface,
                            actualState);
#endif
        }
    }

    Key::State Key::getActualState()
    {
        if (this->contacts.isAsKeyIsReleased())
        {
            return State::released;
        }
        else if (this->contacts.isAsKeyIsDepressed())
        {
            const auto pressingTimeMillis{this->contacts.getKeyPressingTimeMillis()};
            if (pressingTimeMillis <= maxManipulationTimeMillis)
            {
                this->velocity = slope * pressingTimeMillis + maxVelocity;
            }
            else
            {
                this->velocity = 0;
            }

            return State::depressed;
        }
        else
        {
            return State::moving;
        }
    }

    void Key::doSendMidiEvent(const uint8_t firstKeyMidiNoteNumber,
                              const uint8_t midiChannel,
                              MidiInterface &midiInterface,
                              const State actualState)
    {
        const uint8_t noteNumber = this->number + firstKeyMidiNoteNumber;

        switch (actualState)
        {
        case State::depressed:
            midiInterface.sendNoteOn(noteNumber, this->velocity, midiChannel);

#ifdef MIDI_EVENTS_DEBUG_MESSAGES
            char buffer[10];
            Serial.write("ON: note=");
            Serial.write(itoa(noteNumber, buffer, 10));
            Serial.write(", vel=");
            Serial.write(itoa(this->velocity, buffer, 10));
            Serial.write(", time=");
            Serial.write(ltoa(this->contacts.getKeyPressingTimeMillis(), buffer, 10));
            Serial.write("\n");
#endif

            this->previousState = actualState;
            break;

        case State::released:
            midiInterface.sendNoteOff(noteNumber, defaultVelocity, midiChannel);

#ifdef MIDI_EVENTS_DEBUG_MESSAGES
            Serial.write("OFF: note=");
            Serial.write(itoa(noteNumber, buffer, 10));
            Serial.write("\n");
#endif

            this->previousState = actualState;
            break;

        default:
            // Do nothing.
            break;
        }
    }
}