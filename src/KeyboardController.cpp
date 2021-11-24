#include <KeyboardController.hpp>

namespace kbd
{
    KeyboardController::KeyboardController(const std::vector<kbd::KeyboardMatrix> &matrices,
                                           const uint8_t firstKeyMidiNoteNumber) : matrices{matrices},
                                                                                   firstKeyMidiNoteNumber{firstKeyMidiNoteNumber}
    {
    }
}