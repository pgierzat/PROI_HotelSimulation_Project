#ifndef THREE_ROOM_HPP
#define THREE_ROOM_HPP

#include "room.hpp"

class ThreeRoom: public Room
{
    public:
        ThreeRoom(unsigned number);
        unsigned calculatePrice() const override;

};

#endif