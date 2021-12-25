#ifndef ContactMatrices_hpp
#define ContactMatrices_hpp

#include <vector>
#include <array>

#include <ContactMatrix.hpp>

namespace kbd
{
    class ContactMatrices
    {
    private:
        inline static constexpr uint8_t numberOfContactPairGroupsLeft{6};
        inline static constexpr uint8_t numberOfContactPairGroupsRight{5};

        //See the circuit diagram for details regarding inputs/outputs configuration.
        inline static const kbd::ContactMatrix contactMatrixLeft = kbd::ContactMatrix::Builder<numberOfContactPairGroupsLeft>{}
                                                                       .withFirstClosedContactsOutputs({50, 46, 42, 38, 37, 32})
                                                                       .withLastClosedContactsOutputs({52, 48, 44, 40, 36, 34})
                                                                       .withInputs({53, 51, 49, 47, 45, 43, 41, 39})
                                                                       .build();
        inline static const kbd::ContactMatrix contactMatrixRight = kbd::ContactMatrix::Builder<numberOfContactPairGroupsRight>{}
                                                                        .withFirstClosedContactsOutputs({28, 24, 2, 6, 5})
                                                                        .withLastClosedContactsOutputs({30, 26, 22, 4, 7})
                                                                        .withInputs({35, 33, 31, 29, 27, 25, 23, 3})
                                                                        .build();

    public:
        inline static const std::vector<ContactMatrix> contactMatrices{contactMatrixLeft, contactMatrixRight};
    };
}

#endif