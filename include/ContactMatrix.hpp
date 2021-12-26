#ifndef ContactMatrix_hpp
#define ContactMatrix_hpp

#include <vector>
#include <array>

#include <stdint.h>

#include "Contact.hpp"

namespace kbd
{
    class ContactMatrix
    {
    private:
        uint8_t numberOfContactPairGroups;
        uint8_t contactPairsPerGroup;

        //It's supposed that both outputs vectors are of the same size, i.e., numberOfContactPairGroups. This is enforced by ContactMatrix::Builder.
        std::vector<uint8_t> firstClosedContactsOutputs;
        std::vector<uint8_t> lastClosedContactsOutputs;
        //It's supposed that the vectors is of size contactPairsPerGroup. This is enforced by ContactMatrix::Builder.
        std::vector<uint8_t> inputs;

        std::vector<std::vector<Contact>> contacts;

        ContactMatrix(const uint8_t numberOfContactPairGroups,
                      const uint8_t contactPairsPerGroup,
                      const std::vector<uint8_t> &firstClosedContactsOutputs,
                      const std::vector<uint8_t> &lastClosedContactsOutputs,
                      const std::vector<uint8_t> &inputs);

    public:
        const std::vector<std::vector<Contact>> &getContacts();

        uint8_t getNumberOfKeys() const;

        template <uint8_t numberOfContactPairGroups, uint8_t contactPairsPerGroup = 8>
        class Builder
        {
        private:
            std::vector<uint8_t> firstClosedContactsOutputs;
            std::vector<uint8_t> lastClosedContactsOutputs;
            std::vector<uint8_t> inputs;

        public:
            Builder &withFirstClosedContactsOutputs(const std::array<uint8_t, numberOfContactPairGroups> &outputs)
            {
                this->firstClosedContactsOutputs = std::vector<uint8_t>{outputs.begin(), outputs.end()};
                return *this;
            }

            Builder &withLastClosedContactsOutputs(const std::array<uint8_t, numberOfContactPairGroups> &outputs)
            {
                this->lastClosedContactsOutputs = std::vector<uint8_t>{outputs.begin(), outputs.end()};
                return *this;
            }

            Builder &withInputs(const std::array<uint8_t, contactPairsPerGroup> &inputs)
            {
                this->inputs = std::vector<uint8_t>{inputs.begin(), inputs.end()};
                return *this;
            }

            ContactMatrix build() const
            {
                return ContactMatrix{numberOfContactPairGroups,
                                     contactPairsPerGroup,
                                     this->firstClosedContactsOutputs,
                                     this->lastClosedContactsOutputs,
                                     this->inputs};
            }
        };
    };
}

#endif