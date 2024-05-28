#ifndef TWO_ROOM_HPP
#define TWO_ROOM_HPP

#include "room.hpp"

class TwoRoom : public Room
{
    public:
        TwoRoom(unsigned number);
        Amount calculatePrice() const override;
};

#endif