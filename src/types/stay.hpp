#ifndef STAY_HPP
#define STAY_HPP

#include "../rooms/hpp/room.hpp"
#include "datetime.h"
#include "timespan.h"

class Guest;

class Stay
{
    public:
        Stay(Guest, Room, jed_utils::datetime start, jed_utils::datetime end);
    private:
        const Guest& guest;
        const Room& room;
        jed_utils::datetime start;
        jed_utils::datetime end;
};

#endif
