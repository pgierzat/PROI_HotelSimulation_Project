#include "stay.hpp"
#include "../systems/stay_system.hpp"
#include "../systems/guest_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../utilities/errors.hpp"
#include <algorithm>

const StaySystem* Stay::s_system = nullptr;

const GuestSystem* Stay::g_system = nullptr;

const RoomsList* Stay::rooms_list = nullptr;

Stay::Stay(const std::string& id, const Room& room, const Guest& main_guest,
           const jed_utils::datetime& start, const jed_utils::datetime& end) :
    main_guest_id{main_guest.get_id()}, id{id}, start{start}, end{end},
    room_nr{room.getNumber()}
{
    guests_ids.push_back(main_guest_id);
    (this -> start).trunkate();
    (this -> end).trunkate();
    validate_duration(start, end);
}

const std::string& Stay::get_id() const noexcept { return id; }

const std::vector<const Guest*> Stay::get_guests() const
{
    std::vector<const Guest*> guests;
    for (const auto& id : guests_ids)
        guests.push_back(&g_system -> get_by_id(id));
    return guests;
}

const Guest& Stay::get_main_guest() const
{
    return g_system -> get_by_id(main_guest_id);
}

const Room& Stay::get_room() const
{
    return rooms_list -> get_by_number(room_nr);
}

jed_utils::datetime Stay::get_start() const noexcept { return start; }

jed_utils::datetime Stay::get_end() const noexcept { return end; }

TimeInterval Stay::get_interval() const noexcept
{
    return TimeInterval{start + s_system -> checkin_time, end + s_system -> checkout_time};
}

Amount Stay::get_price() const { return get_room().calculatePrice() * get_duration(); }

unsigned Stay::get_duration() const noexcept { return (end - start).get_days(); }

StayStatus Stay::get_status() const noexcept { return status; }

void Stay::add_guest(const Guest& guest)
{
    const auto& id = guest.get_id();
    // if (guests.size() + 1 > room -> getCapacity())
    //     throw RoomCapacityExceededError("Tried to add 'na waleta' Guest", *room);
    auto p = std::ranges::find_if(guests_ids, [&](const auto& otr_id){ return otr_id == id; });
    if (p != guests_ids.end())
        throw std::invalid_argument("Tried to add duplicate Guest.");
    guests_ids.push_back(guest.get_id());
}

void Stay::remove_guest(const Guest& guest)
{
    const auto& id = guest.get_id();
    if (id == main_guest_id)
        throw std::invalid_argument("Cannot remove main Guest from Stay.");
    std::erase_if(guests_ids, [&](const auto& otr_id){ return otr_id == id; });
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

void Stay::set_status(StayStatus status) { this -> status = status; }

bool Stay::operator==(const Stay& other) const
{
    return guests_ids == other.guests_ids &&
        main_guest_id == other.main_guest_id &&
        id == other.id &&
        start == other.start &&
        end == other.end &&
        room_nr == other.room_nr;
}

void Stay::set_s_system(const StaySystem& s_system) { Stay::s_system = &s_system; }
void Stay::set_g_system(const GuestSystem& g_system) { Stay::g_system = &g_system; }
void Stay::set_rooms_list(const RoomsList& rooms_list) { Stay::rooms_list = &rooms_list; }

void Stay::validate_duration(const jed_utils::datetime& start, const jed_utils::datetime& end)
{
    if (start >= end)
        throw std::invalid_argument("Stay must start before it ends.");
}
