#ifndef TWO_APARTMENT_HPP
#define TWO_APARTMENT_HPP

#include "room.hpp"

class TwoAppartment : public Room
{
    public:
        TwoAppartment(const std::string& number);
        Amount calculatePrice() const override;
        unsigned calculatePersonel() const override;
        virtual RoomType get_type() const noexcept override;
        static const RoomType type = RoomType::TwoAppartment;
};


#endif