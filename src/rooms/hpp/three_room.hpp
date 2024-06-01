#ifndef THREE_ROOM_HPP
#define THREE_ROOM_HPP

#include "room.hpp"

class ThreeRoom: public Room
{
    public:
        ThreeRoom(unsigned number);
        Amount calculatePrice() const override;
        virtual RoomType get_type() const noexcept override;
        static const RoomType type = RoomType::ThreeRoom;    
};

#endif