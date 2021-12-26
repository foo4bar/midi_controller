#ifndef Contacts_hpp
#define Contacts_hpp

#include <vector>
#include <array>

#include "ContactMatrix.hpp"

namespace kbd
{
    struct Contacts
    {
    private:
        //Each key is served by a pair of contacts.
        //One of them is closed first when a corresponding key starts to be pressed, 
        //another one is closed last when the key is fully depressed.
        //Mentioned pairs of contacts are divided into two parts, the left one and the right one, each located on its own PCB.
        //Each part in its turn is divided into a number of groups, each group contains 8 pairs of contacts.
        //In total, there are 88 pairs of contacts according to the number of keys.
        inline static constexpr uint8_t numberOfContactPairGroupsLeft{6};
        inline static constexpr uint8_t numberOfContactPairGroupsRight{5};

        //See the circuit diagram for details regarding inputs/outputs configuration.
        inline static const ContactMatrix contactMatrixLeft = ContactMatrix::Builder<numberOfContactPairGroupsLeft>{}
                                                                  .withFirstClosedContactsOutputs({50, 46, 42, 38, 37, 32})
                                                                  .withLastClosedContactsOutputs({52, 48, 44, 40, 36, 34})
                                                                  .withInputs({53, 51, 49, 47, 45, 43, 41, 39})
                                                                  .build();
        inline static const ContactMatrix contactMatrixRight = ContactMatrix::Builder<numberOfContactPairGroupsRight>{}
                                                                   .withFirstClosedContactsOutputs({28, 24, 2, 6, 5})
                                                                   .withLastClosedContactsOutputs({30, 26, 22, 4, 7})
                                                                   .withInputs({35, 33, 31, 29, 27, 25, 23, 3})
                                                                   .build();

    public:
        inline static const std::vector<ContactMatrix> contactMatrices{contactMatrixLeft, contactMatrixRight};
    };
}

#endif