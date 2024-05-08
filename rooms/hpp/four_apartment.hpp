#ifndef FOUR_APARTMENT_HPP
#define FOUR_APARTMENT_HPP

#include "room.hpp"

class FourApartment : public Room
{
    public:
        FourApartment(unsigned number);
        unsigned calculatePrice() const override;
        unsigned calculatePersonel() const override;
};

#endif