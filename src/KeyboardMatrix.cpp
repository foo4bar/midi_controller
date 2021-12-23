#include <KeyboardMatrix.hpp>
#include <DigitalIO.hpp>

namespace kbd
{
    using namespace arduino;

    KeyboardMatrix::KeyboardMatrix(const uint8_t numberOfKeyGroups,
                                   const uint8_t keysPerGroup,
                                   const std::vector<uint8_t> &firstClosedContactsOutputs,
                                   const std::vector<uint8_t> &lastClosedContactsOutputs,
                                   const std::vector<uint8_t> &inputs) : numberOfKeyGroups{numberOfKeyGroups},
                                                                         keysPerGroup{keysPerGroup},
                                                                         firstClosedContactsOutputs{firstClosedContactsOutputs},
                                                                         lastClosedContactsOutputs{lastClosedContactsOutputs},
                                                                         inputs{inputs},
                                                                         contacts{std::vector<std::vector<Contact>>(numberOfKeyGroups, std::vector<Contact>(keysPerGroup))}
    {
        for (const auto &outputs : {firstClosedContactsOutputs, lastClosedContactsOutputs})
            for (const uint8_t output : outputs)
            {
                digital::setPinMode(output, digital::Mode::output);
                digital::setPinState(output, digital::State::high);
            }

        for (const uint8_t input : inputs)
            digital::setPinMode(input, digital::Mode::inputWithInternalPullUp);
    }

    const std::vector<std::vector<Contact>> &KeyboardMatrix::getContacts() //TODO pass contacts as an argument
    {
        for (const auto &outputs : {this->firstClosedContactsOutputs, this->lastClosedContactsOutputs})
            for (uint8_t i = 0; i < this->numberOfKeyGroups; i++)
            {
                digital::setPinState(outputs[i], digital::State::low);

                for (uint8_t j = 0; j < this->keysPerGroup; j++)
                {
                    const auto actualInstantaneousState{digital::getPinState(this->inputs[j]) == digital::State::high
                                                            ? Contact::State::open
                                                            : Contact::State::closed};
                    this->contacts[i][j].updateStateWithDebouncing(actualInstantaneousState);
                }

                digital::setPinState(outputs[i], digital::State::high);
            }

        return this->contacts;
    }

    const uint8_t KeyboardMatrix::getNumberOfKeys() const
    {
        return this->numberOfKeyGroups * this->keysPerGroup;
    }
}
