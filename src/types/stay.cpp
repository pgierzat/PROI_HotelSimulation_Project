#include "stay.hpp"
#include "../systems/stay_system.hpp"
#include "../systems/guest_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../utilities/errors.hpp"
#include <algorithm>


const jed_utils::timespan Stay::checkout_time = jed_utils::timespan{0, 10, 0, 0};

const jed_utils::timespan Stay::checkin_time = jed_utils::timespan{0, 16, 0, 0};

Stay::Stay(const std::string& id, const Room& room, const Guest& main_guest,
           const jed_utils::datetime& start, const jed_utils::datetime& end) :
    RoomObs{room}, GuestsObs{}, id{id}, start{start}, end{end}
{
    GuestsObs::add_observed(main_guest);
    (this -> start).trunkate();
    (this -> end).trunkate();
    validate_duration(start, end);
}

const std::string& Stay::get_id() const noexcept { return id; }

const std::vector<const Guest*> Stay::get_guests() const
{
    return GuestsObs::get();
}

const Guest& Stay::get_main_guest() const
{
    return GuestsObs::front();
}

const Room& Stay::get_room() const
{
    return RoomObs::get();
}

jed_utils::datetime Stay::get_start() const noexcept { return start + checkin_time; }
jed_utils::datetime Stay::get_start_date() const noexcept { return start; }

jed_utils::datetime Stay::get_end() const noexcept { return end + checkout_time; }
jed_utils::datetime Stay::get_end_date() const noexcept { return end; }


TimeInterval Stay::get_interval() const noexcept
{
    return TimeInterval{start + checkin_time, end + checkout_time};
}

Amount Stay::get_price() const { return get_room().calculatePrice() * get_duration(); }

unsigned Stay::get_duration() const noexcept { return (end - start).get_days(); }

StayStatus Stay::get_status() const noexcept { return status; }

void Stay::add_guest(const Guest& guest)
{
    auto& room = get_room();
    if (GuestsObs::size() + 1 > room.getCapacity())
        throw RoomCapacityExceededError("Tried to add 'na waleta' Guest", *this);
    GuestsObs::add_observed(guest);
}

void Stay::set_id(const std::string& id) noexcept { this -> id = id; }

void Stay::remove_guest(const Guest& guest)
{
    const auto& id = guest.get_id();
    if (id == GuestsObs::front().get_id())
        throw std::invalid_argument("Cannot remove main Guest from Stay.");
    GuestsObs::remove_observed(guest);
}

void Stay::set_start(jed_utils::datetime start)
{
    validate_duration(start, end);
    start.trunkate();
    this -> start = start;
}

void Stay::set_end(jed_utils::datetime end)
{
    validate_duration(start, end);
    end.trunkate();
    this -> end = end;
}

void Stay::set_status(StayStatus status) { this -> status = status; }

bool Stay::operator==(const Stay& other) const
{
    return
        id == other.id &&
        GuestsObs::get() == other.GuestsObs::get() &&
        RoomObs::get_observed_id() == other.RoomObs::get_observed_id() &&
        start == other.start &&
        end == other.end;
}

void Stay::validate_duration(const jed_utils::datetime& start, const jed_utils::datetime& end)
{
    if (start >= end)
        throw std::invalid_argument("Stay must start before it ends.");
}
