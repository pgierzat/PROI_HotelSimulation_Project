#ifndef FOUR_ROOM_HPP
#define FOUR_ROOM_HPP

#include "room.hpp"

class FourRoom: public Room
{
    public:
        FourRoom(unsigned number);
        Amount calculatePrice() const override;

};


#endif