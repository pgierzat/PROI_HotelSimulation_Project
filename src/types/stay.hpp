#ifndef STAY_HPP
#define STAY_HPP

#include "../rooms/hpp/room.hpp"
#include "datetime.h"
#include "timespan.h"
#include "guest.hpp"
#include "time_interval.hpp"


class Stay
{
    public:
        Stay(const Guest&, const Room&, const jed_utils::datetime& start, const jed_utils::datetime& end);
        Guest get_guest() const;
        Room get_room() const;
        jed_utils::datetime get_start() const noexcept;
        jed_utils::datetime get_end() const noexcept;
        TimeInterval get_interval() const noexcept;
        void set_start(const jed_utils::datetime start);
        void set_end(const jed_utils::datetime end);
    private:
        static void validate_duration(const jed_utils::datetime& start, const jed_utils::datetime& end);
        const Guest& guest;
        const Room& room;
        jed_utils::datetime start;
        jed_utils::datetime end;
};

#endif
