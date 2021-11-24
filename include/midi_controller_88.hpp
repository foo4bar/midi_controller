#ifndef midi_controller_88_hpp
#define midi_controller_88_hpp

#include <stdint.h>
#include <KeyboardMatrix.hpp>
#include <KeyboardController.hpp>

inline constexpr uint8_t number_of_key_groups_left{6};
inline constexpr uint8_t number_of_key_groups_right{5};
inline constexpr uint8_t first_key_note_number{21};

//See the circuit diagram for details regarding inputs/outputs configuration.
inline const kbd::KeyboardMatrix keyboardMatrixLeft = kbd::KeyboardMatrix::Builder<number_of_key_groups_left>{}
                                                          .withFirstClosedContactsOutputs({50, 46, 42, 38, 37, 32})
                                                          .withLastClosedContactsOutputs({52, 48, 44, 40, 36, 34})
                                                          .withInputs({53, 51, 49, 47, 45, 43, 41, 39})
                                                          .build();
inline const kbd::KeyboardMatrix keyboardMatrixRight = kbd::KeyboardMatrix::Builder<number_of_key_groups_right>{}
                                                           .withFirstClosedContactsOutputs({28, 24, 2, 6, 5})
                                                           .withLastClosedContactsOutputs({30, 26, 22, 4, 7})
                                                           .withInputs({35, 33, 31, 29, 27, 25, 23, 3})
                                                           .build();
inline const kbd::KeyboardController keyboardController{{keyboardMatrixLeft, keyboardMatrixRight}, first_key_note_number};

#endif