#ifndef STAY_HPP
#define STAY_HPP

#include "../rooms/hpp/room.hpp"
#include "datetime.h"
#include "timespan.h"
#include "guest.hpp"


class Stay
{
    public:
        Stay(const Guest&, const Room&, const jed_utils::datetime& start, const jed_utils::datetime& end);
    private:
        const Guest& guest;
        const Room& room;
        jed_utils::datetime start;
        jed_utils::datetime end;
};

#endif
