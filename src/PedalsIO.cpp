#include "PedalsIO.hpp"

namespace kbd
{
    State PedalsIO::getActualInstantaneousInputState(const Pedal::Function pedalFuction) const
    {
        return this->inputs.find(pedalFuction)->second.getState();
    }

    PedalsIO::PedalsIO(const std::map<Pedal::Function, Pin> &inputs) : inputs{inputs}
    {
    }
}