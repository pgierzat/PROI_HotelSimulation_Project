#include "stay.hpp"
#include "../systems/stay_system.hpp"
#include "../systems/guest_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../utilities/errors.hpp"
#include <algorithm>


const StaySystem* Stay::s_system = nullptr;

Stay::Stay(const std::string& id, const Room& room, const Guest& main_guest,
           const jed_utils::datetime& start, const jed_utils::datetime& end) :
    room_observer{room.get_id()}, main_guest_id{main_guest.get_id()}, id{id}, start{start}, end{end}
{
    guest_observers.emplace_back(main_guest_id);
    (this -> start).trunkate();
    (this -> end).trunkate();
    validate_duration(start, end);
}

const std::string& Stay::get_id() const noexcept { return id; }

const std::vector<const Guest*> Stay::get_guests() const
{
    std::vector<const Guest*> guests;
    for (const auto& observer : guest_observers)
        guests.push_back(&observer.get_observed());
    return guests;
}

std::vector<const std::string*> Stay::get_guest_ids() const noexcept
{
    std::vector<const std::string*> guests;
    for (const auto& observer : guest_observers)
        guests.push_back(&observer.get_observed_id());
    return guests;
}

std::vector<OwnSystemObserver<Guest>*> Stay::get_guest_observers() noexcept
{
    std::vector<OwnSystemObserver<Guest>*> gobs;
    for (auto& observer : guest_observers)
        gobs.push_back(&observer);
    return gobs;
}

OwnSystemObserver<Guest>& Stay::get_guest_observer(const std::string& id)
{
    auto p = std::ranges::find_if(guest_observers,
        [&](const auto& obs){ return obs.get_observed_id() == id; });
    if (p == guest_observers.end())
        throw std::invalid_argument("Guest observer not found among Stay's observers.");
    return *p;
}

const std::string& Stay::get_main_guest_id() const noexcept { return main_guest_id; }

const Guest& Stay::get_main_guest() const
{
    auto p = std::ranges::find_if(guest_observers,
        [&](const auto& obs){ return obs.get_observed().get_id() == main_guest_id; });
    return p -> get_observed();
}

const std::string& Stay::get_room_id() const noexcept { return room_observer.get_observed_id(); }

const Room& Stay::get_room() const
{
    return room_observer.get_observed();
}

OwnSystemObserver<Room>& Stay::get_room_observer() noexcept { return room_observer; }

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
    auto room = get_room();
    if (guest_observers.size() + 1 > room.getCapacity())
        throw RoomCapacityExceededError("Tried to add 'na waleta' Guest", *this);
    auto p = std::ranges::find_if(guest_observers,
        [&](const auto& obs){ return obs.get_observed().get_id() == id; });
    if (p != guest_observers.end())
        throw std::invalid_argument("Tried to add duplicate Guest to a Stay.");
    guest_observers.emplace_back(guest.get_id());
}

void Stay::remove_guest(const Guest& guest)
{
    const auto& id = guest.get_id();
    if (id == main_guest_id)
        throw std::invalid_argument("Cannot remove main Guest from Stay.");
    std::erase_if(guest_observers, [&](const auto& obs){ return obs.get_observed_id() == id; });
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
    return
        id == other.id &&
        main_guest_id == other.main_guest_id &&
        get_room_id() == other.get_room_id() &&
        start == other.start &&
        end == other.end;
}

void Stay::validate_duration(const jed_utils::datetime& start, const jed_utils::datetime& end)
{
    if (start >= end)
        throw std::invalid_argument("Stay must start before it ends.");
}

void Stay::set_s_system(const StaySystem& s_system) { Stay::s_system = &s_system; }
