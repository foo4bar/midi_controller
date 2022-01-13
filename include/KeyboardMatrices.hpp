#ifndef KeyboardMatrices_hpp
#define KeyboardMatrices_hpp

#include <stdint.h>
#include <Arduino.h>

#include "DigitalIO.hpp"
#include "KeyboardMatrixIO.hpp"

namespace kbd
{
    //See the circuit diagram for details regarding inputs/outputs configuration.
    inline constexpr uint8_t numberOfOutputPairsLeft{6};
    inline constexpr uint8_t numberOfOutputPairsRight{5};
    inline constexpr uint8_t numberOfInputs{8};

    inline constexpr uint8_t numberOfScannedKeysLeft{numberOfOutputPairsLeft * numberOfInputs};
    inline constexpr uint8_t numberOfScannedKeysRight{numberOfOutputPairsRight * numberOfInputs};
    inline constexpr uint8_t numberOfScannedKeys{numberOfScannedKeysLeft + numberOfScannedKeysRight};

    inline auto keyboardMatrixIOLeft{KeyboardMatrixIO::Builder{.firstClosedContactsOutputs{50, 46, 42, 38, 37, 32},
                                                               .lastClosedContactsOutputs{52, 48, 44, 40, 36, 34},
                                                               .inputs{53, 51, 49, 47, 45, 43, 41, 39}}
                                         .build()};
    inline auto keyboardMatrixIORight{KeyboardMatrixIO::Builder{.firstClosedContactsOutputs{28, 24, 2, 6, 5},
                                                                .lastClosedContactsOutputs{30, 26, 22, 4, 7},
                                                                .inputs{35, 33, 31, 29, 27, 25, 23, 3}}
                                          .build()};

    const arduino::digital::InputStatePair getActualInstantaneousInputStatePair(const uint8_t keyNumber);

    class KeyboardMatricesIO
    {
    private:
        std::vector<KeyboardMatrixIO> keyboardMatrices;

    public:
        const arduino::digital::InputStatePair getActualInstantaneousInputStatePair(const uint8_t keyNumber);
    };
}

#endif