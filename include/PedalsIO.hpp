#ifndef PedalsIO_hpp
#define PedalsIO_hpp

#include <map>

#include "DigitalIO.hpp"
#include "Pedal.hpp"

namespace kbd
{
    using namespace arduino::digital;

    class PedalsIO
    {
    public:
        explicit PedalsIO(const std::map<Pedal::Function, Pin> &inputs);

        State getActualInstantaneousInputState(const Pedal::Function) const;

    private:
        const std::map<Pedal::Function, Pin> inputs;
    };
}

#endif