#include "Key.hpp"
#include "KeyboardController.hpp"

namespace kbd
{
    void Key::sendMidiEvent(const uint8_t midiNoteNumber,
                            MidiInterface &midiInterface,
                            const arduino::digital::KeyInputStates &keyInputStates)
    {
        this->contacts.updateStateWithDebouncing(keyInputStates);
        const auto actualState{getActualState()};

        if (actualState == State::moving || this->previousState == actualState)
        {
            // Do nothing.
        }
        else
        {
#if !defined(AVR_STUB_DEBUG) && !defined(CONTACT_EVENTS_DEBUG_MESSAGES)
            doSendMidiEvent(midiNoteNumber,
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
            if (pressingTimeMillis <= Key::maxManipulationTimeMillis)
            {
                this->velocity = Key::slope * pressingTimeMillis + Key::maxVelocity;
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

    void Key::doSendMidiEvent(const uint8_t midiNoteNumber,
                              MidiInterface &midiInterface,
                              const State actualState)
    {
        switch (actualState)
        {
        case State::depressed:
            midiInterface.sendNoteOn(midiNoteNumber, this->velocity, KeyboardController::midiChannel);

#ifdef MIDI_EVENTS_DEBUG_MESSAGES
            char buffer[10];
            Serial.write("ON: note=");
            Serial.write(itoa(midiNoteNumber, buffer, 10));
            Serial.write(", vel=");
            Serial.write(itoa(this->velocity, buffer, 10));
            Serial.write(", time=");
            Serial.write(ltoa(this->contacts.getKeyPressingTimeMillis(), buffer, 10));
            Serial.write("\n");
#endif

            this->previousState = actualState;
            break;

        case State::released:
            midiInterface.sendNoteOff(midiNoteNumber, Key::noteOffVelocity, KeyboardController::midiChannel);

#ifdef MIDI_EVENTS_DEBUG_MESSAGES
            Serial.write("OFF: note=");
            Serial.write(itoa(midiNoteNumber, buffer, 10));
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
