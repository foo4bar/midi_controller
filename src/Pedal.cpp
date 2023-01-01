#include "Pedal.hpp"

namespace kbd
{
    Pedal::Pedal(const uint8_t number, const Function function) : number{number},
                                                                  function{function}
    {
    }

    void Pedal::sendMidiEvent(const uint8_t midiChannel,
                              MidiInterface &midiInterface,
                              PedalsIO &pedalIO)
    {
        this->contact.updateStateWithDebouncing(pedalIO.getActualInstantaneousInputState(this->number));

        const State actualState{getActualState()};

        if (this->previousState == actualState)
        {
            // Do nothing.
        }
        else
        {
#if !defined(AVR_STUB_DEBUG) && !defined(CONTACT_EVENTS_DEBUG_MESSAGES)
            doSendMidiEvent(midiChannel,
                            midiInterface,
                            actualState);
#endif
        }
    }

    Pedal::State Pedal::getActualState()
    {
        if (this->contact.isClosed())
        {
            return State::depressed;
        }
        else
        {
            return State::released;
        }
    }

    void Pedal::doSendMidiEvent(const uint8_t midiChannel,
                                MidiInterface &midiInterface,
                                const State actualState)
    {

        switch (actualState)
        {
        case State::depressed:
            midiInterface.sendControlChange(static_cast<uint8_t>(this->function), 127, midiChannel);

#ifdef MIDI_EVENTS_DEBUG_MESSAGES
            char buffer[10];
            Serial.write("ON: pedal=");
            Serial.write(itoa(this->function, buffer, 10));
            Serial.write("\n");
#endif

            this->previousState = actualState;
            break;

        case State::released:
            midiInterface.sendControlChange(static_cast<uint8_t>(this->function), 0, midiChannel);

#ifdef MIDI_EVENTS_DEBUG_MESSAGES
            Serial.write("OFF: pedal=");
            Serial.write(itoa(this->function, buffer, 10));
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