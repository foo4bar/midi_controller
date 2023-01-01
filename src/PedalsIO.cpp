#include "PedalsIO.hpp"

namespace kbd
{
    State PedalsIO::getActualInstantaneousInputState(const uint8_t pedalNumber) const
    {
        return this->inputs[pedalNumber].getState();
    }

    PedalsIO::PedalsIO(const std::vector<Pin> &inputs) : inputs{inputs}
    {
    }
}