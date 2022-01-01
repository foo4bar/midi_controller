#ifndef KeyboardMatrixIO_hpp
#define KeyboardMatrixIO_hpp

#include <vector>
#include <array>

#include <stdint.h>

#include "DigitalIO.hpp"

namespace kbd
{   
    using namespace arduino::digital;
    
    class KeyboardMatrixIO
    {
    private:
        uint8_t numberOfOutputPairs;
        uint8_t numberOfInputs;

        //It's supposed that both outputs vectors are of the same size, i.e., numberOfOutputPairs. This is enforced by KeyboardMatrixIO::Builder.
        std::vector<uint8_t> firstClosedContactsOutputs;
        std::vector<uint8_t> lastClosedContactsOutputs;
        //It's supposed that the vectors is of size numberOfInputs. This is enforced by KeyboardMatrixIO::Builder.
        std::vector<uint8_t> inputs;

        KeyboardMatrixIO(const uint8_t numberOfOutputPairs,
                         const uint8_t numberOfInputs,
                         const std::vector<uint8_t> &firstClosedContactsOutputs,
                         const std::vector<uint8_t> &lastClosedContactsOutputs,
                         const std::vector<uint8_t> &inputs);

    public:
        const StatePair getActualInstantaneousInputStatePair(const uint8_t contactPairNumber) const;

        template <uint8_t numberOfOutputPairs, uint8_t numberOfInputs>
        class Builder
        {
        private:
            std::vector<uint8_t> firstClosedContactsOutputs;
            std::vector<uint8_t> lastClosedContactsOutputs;
            std::vector<uint8_t> inputs;

        public:
            Builder &withFirstClosedContactsOutputs(const std::array<uint8_t, numberOfOutputPairs> &outputs)
            {
                this->firstClosedContactsOutputs = std::vector<uint8_t>{outputs.begin(), outputs.end()};
                return *this;
            }

            Builder &withLastClosedContactsOutputs(const std::array<uint8_t, numberOfOutputPairs> &outputs)
            {
                this->lastClosedContactsOutputs = std::vector<uint8_t>{outputs.begin(), outputs.end()};
                return *this;
            }

            Builder &withInputs(const std::array<uint8_t, numberOfInputs> &inputs)
            {
                this->inputs = std::vector<uint8_t>{inputs.begin(), inputs.end()};
                return *this;
            }

            KeyboardMatrixIO build() const
            {
                return KeyboardMatrixIO{numberOfOutputPairs,
                                        numberOfInputs,
                                        this->firstClosedContactsOutputs,
                                        this->lastClosedContactsOutputs,
                                        this->inputs};
            }
        };
    };
}

#endif