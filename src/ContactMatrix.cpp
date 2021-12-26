#include "DigitalIO.hpp"
#include "ContactMatrix.hpp"

namespace kbd
{
    using namespace arduino;

    ContactMatrix::ContactMatrix(const uint8_t numberOfContactPairGroups,
                                 const uint8_t contactPairsPerGroup,
                                 const std::vector<uint8_t> &firstClosedContactsOutputs,
                                 const std::vector<uint8_t> &lastClosedContactsOutputs,
                                 const std::vector<uint8_t> &inputs) : numberOfContactPairGroups{numberOfContactPairGroups},
                                                                       contactPairsPerGroup{contactPairsPerGroup},
                                                                       firstClosedContactsOutputs{firstClosedContactsOutputs},
                                                                       lastClosedContactsOutputs{lastClosedContactsOutputs},
                                                                       inputs{inputs},
                                                                       contacts{std::vector<std::vector<Contact>>(numberOfContactPairGroups, std::vector<Contact>(contactPairsPerGroup))}
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

    const std::vector<std::vector<Contact>> &ContactMatrix::scanContactsAndGet()
    {
        for (const auto &outputs : {this->firstClosedContactsOutputs, this->lastClosedContactsOutputs})
            for (uint8_t i = 0; i < this->numberOfContactPairGroups; i++)
            {
                digital::setPinState(outputs[i], digital::State::low);

                for (uint8_t j = 0; j < this->contactPairsPerGroup; j++)
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

    uint8_t ContactMatrix::getNumberOfKeys() const
    {
        return this->numberOfContactPairGroups * this->contactPairsPerGroup;
    }
}
