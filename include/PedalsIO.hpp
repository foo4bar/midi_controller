#ifndef PedalsIO_hpp
#define PedalsIO_hpp

#include <vector>

#include "DigitalIO.hpp"

namespace kbd
{
    using namespace arduino::digital;

    class PedalsIO
    {
    public:
        PedalsIO(const std::vector<Pin> &inputs);

        State getActualInstantaneousInputState(const uint8_t pedalNumber) const;

    private:
        const std::vector<Pin> inputs;
    };
}

#endif