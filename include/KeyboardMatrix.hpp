#ifndef KeyboardMatrix_hpp
#define KeyboardMatrix_hpp

#include <stdint.h>
#include <Contact.hpp>

#include <vector>
#include <array>

namespace kbd
{
    class KeyboardMatrix
    {
    private:
        uint8_t numberOfKeyGroups;
        uint8_t keysPerGroup;

        //It's supposed that both outputs vectors are of the same size, i.e., numberOfKeyGroups. This is enforced by KeyboardMatrix::Builder.
        std::vector<uint8_t> firstClosedContactsOutputs;
        std::vector<uint8_t> lastClosedContactsOutputs;
        //It's supposed that the vectors is of size keysPerGroup. This is enforced by KeyboardMatrix::Builder.
        std::vector<uint8_t> inputs;

        std::vector<std::vector<Contact>> contacts;

        KeyboardMatrix(const uint8_t numberOfKeyGroups,
                       const uint8_t keysPerGroup,
                       const std::vector<uint8_t> &firstClosedContactsOutputs,
                       const std::vector<uint8_t> &lastClosedContactsOutputs,
                       const std::vector<uint8_t> &inputs);

    public:
        void scan();

        const uint8_t getNumberOfKeys() const;

        template <uint8_t numberOfKeyGroups, uint8_t keysPerGroup = 8>
        class Builder
        {
        private:
            std::vector<uint8_t> firstClosedContactsOutputs;
            std::vector<uint8_t> lastClosedContactsOutputs;
            std::vector<uint8_t> inputs;

        public:
            Builder &withFirstClosedContactsOutputs(const std::array<uint8_t, numberOfKeyGroups> &outputs)
            {
                this->firstClosedContactsOutputs = std::vector<uint8_t>{outputs.begin(), outputs.end()};
                return *this;
            }

            Builder &withLastClosedContactsOutputs(const std::array<uint8_t, numberOfKeyGroups> &outputs)
            {
                this->lastClosedContactsOutputs = std::vector<uint8_t>{outputs.begin(), outputs.end()};
                return *this;
            }

            Builder &withInputs(const std::array<uint8_t, keysPerGroup> &inputs)
            {
                this->inputs = std::vector<uint8_t>{inputs.begin(), inputs.end()};
                return *this;
            }

            KeyboardMatrix build() const
            {
                return KeyboardMatrix{numberOfKeyGroups,
                                      keysPerGroup,
                                      this->firstClosedContactsOutputs,
                                      this->lastClosedContactsOutputs,
                                      this->inputs};
            }
        };
    };
}

#endif