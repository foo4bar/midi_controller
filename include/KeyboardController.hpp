#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <stdint.h>
#include <KeyboardMatrix.hpp>

#include <vector>

namespace kbd
{
    enum class KeyEvent
    {
        depressed,
        released
    };

    class KeyboardController
    {
    private:
        std::vector<kbd::ContactMatrix> matrices;
        uint8_t firstKeyMidiNoteNumber;

    public:
        KeyboardController(const std::vector<kbd::ContactMatrix> &matrices, const uint8_t firstKeyMidiNoteNumber);
    };

}

#endif