#ifndef FOUR_ROOM_HPP
#define FOUR_ROOM_HPP

#include "room.hpp"

class FourRoom: public Room
{
    public:
        FourRoom(const std::string& number);
        Amount calculatePrice() const override;
        virtual RoomType get_type() const noexcept override;
        static const RoomType type = RoomType::FourRoom;

};


#endif