#ifndef DigitalIO_hpp
#define DigitalIO_hpp

#include <vector>
#include <array>

#include <stdint.h>

//Serves as a kind of HAL to decouple of C stuff in Arduino.h.
namespace arduino::digital
{
    enum class State : uint8_t
    {
        low = 0, //LOW in Arduino.h
        high = 1 //HIGH in Arduino.h
    };

    enum class Mode : uint8_t
    {
        input = 0,                  //INPUT in Arduino.h
        output = 1,                 //OUTPUT in Arduino.h
        inputWithInternalPullUp = 2 //INPUT_PULLUP in Arduino.h
    };

    struct StatePair
    {
        State firstClosed{State::high};
        State lastClosed{State::high};
    };

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

    //See the circuit diagram for details regarding inputs/outputs configuration.
    inline constexpr uint8_t numberOfOutputPairsLeft{6};
    inline constexpr uint8_t numberOfOutputPairsRight{5};
    inline constexpr uint8_t numberOfInputs{8};

    inline constexpr uint8_t numberOfScannedContactPairs = (numberOfOutputPairsLeft + numberOfOutputPairsRight) * numberOfInputs;

    inline const KeyboardMatrixIO keyboardMatrixIOLeft = KeyboardMatrixIO::Builder<numberOfOutputPairsLeft, numberOfInputs>{}
                                                             .withFirstClosedContactsOutputs({50, 46, 42, 38, 37, 32})
                                                             .withLastClosedContactsOutputs({52, 48, 44, 40, 36, 34})
                                                             .withInputs({53, 51, 49, 47, 45, 43, 41, 39})
                                                             .build();
    inline const KeyboardMatrixIO keyboardMatrixIORight = KeyboardMatrixIO::Builder<numberOfOutputPairsRight, numberOfInputs>{}
                                                              .withFirstClosedContactsOutputs({28, 24, 2, 6, 5})
                                                              .withLastClosedContactsOutputs({30, 26, 22, 4, 7})
                                                              .withInputs({35, 33, 31, 29, 27, 25, 23, 3})
                                                              .build();

    void setPinMode(const uint8_t pinNumber, const Mode mode);

    const State getPinState(const uint8_t pinNumber);

    void setPinState(const uint8_t pinNumber, const State state);

    const StatePair getActualInstantaneousInputStatePair(const uint8_t contactPairNumber);
}

#endif