#ifndef KeyboardMatrices_hpp
#define KeyboardMatrices_hpp

#include <stdint.h>
#include <Arduino.h>

#include "DigitalIO.hpp"
#include "KeyboardMatrixIO.hpp"

namespace kbdmatrix
{
    //See the circuit diagram for details regarding inputs/outputs configuration.
    inline constexpr uint8_t numberOfOutputPairsLeft{6};
    inline constexpr uint8_t numberOfOutputPairsRight{5};
    inline constexpr uint8_t numberOfInputs{8};

    inline constexpr uint8_t numberOfScannedKeysLeft = numberOfOutputPairsLeft * numberOfInputs;
    inline constexpr uint8_t numberOfScannedKeysRight = numberOfOutputPairsRight * numberOfInputs;
    inline constexpr uint8_t numberOfScannedKeys = numberOfScannedKeysLeft + numberOfScannedKeysRight;

    inline const KeyboardMatrixIO keyboardMatrixIOLeft = KeyboardMatrixIO::Builder<numberOfOutputPairsLeft, numberOfInputs>{}
                                                             .withFirstClosedContactsOutputs({portB[3],
                                                                                              portL[3],
                                                                                              portL[7],
                                                                                              portD[7],
                                                                                              portC[0],
                                                                                              portC[5]})
                                                             .withLastClosedContactsOutputs({portB[1],
                                                                                             portL[1],
                                                                                             portL[5],
                                                                                             portG[1],
                                                                                             portC[1],
                                                                                             portC[3]})
                                                             .withInputs({53, 51, 49, 47, 45, 43, 41, 39})
                                                             .build();
    inline const KeyboardMatrixIO keyboardMatrixIORight = KeyboardMatrixIO::Builder<numberOfOutputPairsRight, numberOfInputs>{}
                                                              .withFirstClosedContactsOutputs({portA[6],
                                                                                               portA[2],
                                                                                               portE[4],
                                                                                               portH[3],
                                                                                               portE[3]})
                                                              .withLastClosedContactsOutputs({portC[7],
                                                                                              portA[4],
                                                                                              portA[0],
                                                                                              portG[5],
                                                                                              portH[4]})
                                                              .withInputs({35, 33, 31, 29, 27, 25, 23, 3})
                                                              .build();

    const arduino::digital::InputStatePair getActualInstantaneousInputStatePair(const uint8_t keyNumber);
}

#endif