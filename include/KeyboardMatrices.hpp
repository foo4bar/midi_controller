#ifndef KeyboardMatrices_hpp
#define KeyboardMatrices_hpp

#include "DigitalIO.hpp"
#include "KeyboardMatrixIO.hpp"

namespace kbdmatrix
{
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

    const arduino::digital::StatePair getActualInstantaneousInputStatePair(const uint8_t);
}

#endif