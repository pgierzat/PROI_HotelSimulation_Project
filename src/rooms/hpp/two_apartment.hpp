#ifndef TWO_APARTMENT_HPP
#define TWO_APARTMENT_HPP

#include "room.hpp"

class TwoApartment : public Room
{
    public:
        TwoApartment(unsigned number);
        Amount calculatePrice() const override;
        unsigned calculatePersonel() const override;
};


#endif