#include <KeyboardController.hpp>

namespace kbd
{
    KeyboardController::KeyboardController(const std::vector<kbd::ContactMatrix> &matrices,
                                           const uint8_t firstKeyMidiNoteNumber) : matrices{matrices},
                                                                                   firstKeyMidiNoteNumber{firstKeyMidiNoteNumber}
    {
    }
}