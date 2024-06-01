#ifndef FOUR_APARTMENT_HPP
#define FOUR_APARTMENT_HPP

#include "room.hpp"

class FourAppartment : public Room
{
    public:
        FourAppartment(unsigned number);
        Amount calculatePrice() const override;
        unsigned calculatePersonel() const override;
        virtual RoomType get_type() const noexcept override;
        static const RoomType type = RoomType::FourAppartment;
};

#endif