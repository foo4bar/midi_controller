#include "IOMatrices.hpp"

namespace arduino::digital
{
    IOMatrices::IOMatrices(const std::vector<IOMatrix> &ioMatrices) : ioMatrices{ioMatrices}
    {
        this->numberOfKeysBeingScanned =
            static_cast<uint8_t>(std::accumulate(ioMatrices.begin(),
                                                 ioMatrices.end(),
                                                 0,
                                                 [](uint8_t init, const IOMatrix &ioMatrix)
                                                 { return init + ioMatrix.getNumberOfKeysBeingScanned(); }));
    }

    uint8_t IOMatrices::getNumberOfKeysBeingScanned() const
    {
        return this->numberOfKeysBeingScanned;
    }

    std::vector<KeyInputStates> IOMatrices::getActualInstantaneousKeysInputsStates() const
    {
        std::vector<KeyInputStates> keysInputStates{};

        for (const auto &ioMatrix : this->ioMatrices)
        {
            const auto actualInstantaneousKeysInputsStates{ioMatrix.getActualInstantaneousKeysInputsStates()};
            keysInputStates.insert(keysInputStates.end(),
                                   actualInstantaneousKeysInputsStates.begin(),
                                   actualInstantaneousKeysInputsStates.end());
        }

        return keysInputStates;
    }
}