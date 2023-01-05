#include "IOMatrices.hpp"

namespace kbd
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

    arduino::digital::KeyInputStates IOMatrices::getActualInstantaneousKeyInputStates(const uint8_t keyNumber) const
    {
        uint8_t numberOfKeysBeingScannedByPreviousMatrices{};
        for (const auto &ioMatrix : this->ioMatrices)
        {
            if (keyNumber < (ioMatrix.getNumberOfKeysBeingScanned() + numberOfKeysBeingScannedByPreviousMatrices))
            {
                return ioMatrix.getActualInstantaneousKeyInputStates(keyNumber - numberOfKeysBeingScannedByPreviousMatrices);
            }
            else
            {
                numberOfKeysBeingScannedByPreviousMatrices += ioMatrix.getNumberOfKeysBeingScanned();
            }
        }

        return arduino::digital::KeyInputStates{};
    }
}