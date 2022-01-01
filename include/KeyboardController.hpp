#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include <stdint.h>

#include "Key.hpp"
#include "KeyboardMatrices.hpp"

namespace kbd
{
    class KeyboardController
    {
    private:
        static inline constexpr uint8_t numberOfKeys{numberOfScannedContactPairs};

        KeyboardController();

        std::vector<Key> keys;

    public:
        static inline KeyboardController &getInstance()
        {
            static KeyboardController instance;

            return instance;
        }

        void sendMidiEvents();

        KeyboardController(const KeyboardController &) = delete;
        void operator=(const KeyboardController &) = delete;
    };
}

#endif