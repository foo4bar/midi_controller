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

    std::vector<KeyInputStates> IOMatrices::getActualInstantaneousKeysInputStates() const
    {
        std::vector<KeyInputStates> keysInputStates;

        for (uint8_t keyNumber{0}; keyNumber < this->numberOfKeysBeingScanned; ++keyNumber)
        {
            keysInputStates.push_back(this->getActualInstantaneousKeyInputStates(keyNumber));
        }

        return keysInputStates;
    }

    KeyInputStates IOMatrices::getActualInstantaneousKeyInputStates(const uint8_t keyNumber) const
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

        return KeyInputStates{};
    }
}