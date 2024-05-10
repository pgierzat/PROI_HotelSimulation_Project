#include "stay.hpp"

Stay::Stay(const Guest& guest, const Room& room, const jed_utils::datetime& start,
    const jed_utils::datetime& end) : guest{guest}, room{room}, start{start}, end{end}
{
    (this -> start).trunkate();
    (this -> end).trunkate();
    validate_duration(start, end);
}

Guest Stay::get_guest() const { return guest; }

Room Stay::get_room() const { return room; }

jed_utils::datetime Stay::get_start() const noexcept { return start; }

jed_utils::datetime Stay::get_end() const noexcept { return end; }

TimeInterval Stay::get_interval() const noexcept { return TimeInterval{start, end}; }

void Stay::set_start(const jed_utils::datetime start)
{
    validate_duration(start, end);
    this -> start = start;
}

void Stay::set_end(const jed_utils::datetime end)
{
    validate_duration(start, end);
    this -> end = end;
}

void Stay::validate_duration(const jed_utils::datetime& start, const jed_utils::datetime& end)
{
    if (start >= end)
        throw std::invalid_argument("Stay must start before it ends.");
}
