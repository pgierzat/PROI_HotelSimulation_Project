#include "stay.hpp"
#include "../utilities/errors.hpp"
#include <algorithm>

Stay::Stay(const Room& room, const jed_utils::datetime& start,
    const jed_utils::datetime& end) : room{&room}, start{start}, end{end}
{
    (this -> start).trunkate();
    (this -> end).trunkate();
    validate_duration(start, end);
}

const std::vector<const Guest*>& Stay::get_guests() const { return guests; }

const Room& Stay::get_room() const { return *room; }

jed_utils::datetime Stay::get_start() const noexcept { return start; }

jed_utils::datetime Stay::get_end() const noexcept { return end; }

TimeInterval Stay::get_interval() const noexcept { return TimeInterval{start, end}; }

void Stay::add_guest(const Guest& guest)
{
    if (guests.size() + 1 > room -> getCapacity())
        throw RoomCapacityExceededError("Tried to add 'na waleta' Guest", *room);
    auto p = std::ranges::find_if(guests, [&](const Guest* otr_guest){ return *otr_guest == guest; });
    if (p != guests.end())
        throw std::invalid_argument("Tried to add duplicate Guest.");
    guests.push_back(&guest);
}

void Stay::remove_guest(const Guest& guest)
{
    std::erase_if(guests, [&](const Guest* otr_guest){ return *otr_guest == guest; });
}

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

bool Stay::operator==(const Stay& other) const
{
    return *room == *other.room &&
        start == other.start &&
        end == other.end &&
        std::ranges::equal(guests, other.guests,
            [](const Guest* lhs, const Guest* rhs){ return *lhs == *rhs; });
}