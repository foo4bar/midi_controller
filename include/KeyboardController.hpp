#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <vector>

#include "Key.hpp"

namespace kbd
{
    class KeyboardController
    {
    private:
        std::vector<Key> keys;

    public:
        KeyboardController(const std::vector<Key> &);

        void sendMidiEvents();
    };
}

#endif