#include "stay_system.hpp"
#include "../utilities/errors.hpp"
#include <ranges>
#include <algorithm>

const jed_utils::timespan StaySystem::checkout_time = jed_utils::timespan{0, 10, 0, 0};

const jed_utils::timespan StaySystem::checkin_time = jed_utils::timespan{0, 16, 0, 0};

void StaySystem::bind_guest_system(const GuestSystem& g_system)
{
    this -> g_system = &g_system;
}

void StaySystem::bind_room_system(const RoomsList& rooms_list)
{
    this -> rooms_list = &rooms_list;
}

void StaySystem::add_stay(const Stay& stay)
{
    validate_guests(stay);
    validate_room(stay.get_room());
    check_overlap(stay);
    stays.push_back(stay);
}

void StaySystem::remove_stay(const Stay& stay) { std::erase(stays, stay); }

const std::vector<Stay>& StaySystem::get_stays() const noexcept { return stays; }

void StaySystem::check_overlap(const Stay& stay)
{
    const auto& room = stay.get_room();
    auto interval = stay.get_interval();
    auto room_stays = std::ranges::filter_view(stays,
        [&](const auto & otr_stay){ return otr_stay.get_room() == room; });
    auto p = std::ranges::find_if(room_stays,
        [&](const auto& otr_stay){ return distance( interval, otr_stay.get_interval() ) < jed_utils::timespan{0}; });
    if ( p != room_stays.end() )
        throw StayOverlapError("Attempt to add overlapping stay.", *p, stay);
}

void StaySystem::validate_guest(const Guest& guest)
{
    if( !(g_system -> has_guest(guest)) )
        throw GuestNotInSystemError("Tried to add a stay with unknown Guest.", guest);
}

void StaySystem::validate_guests(const Stay& stay)
{
    auto stay_guests = stay.get_guests();
    if (stay_guests.empty())
        throw std::invalid_argument("Tried to add stay that has no guests.");
    for (const Guest* guest : stay_guests)
        validate_guest(*guest);
}

void StaySystem::validate_room(const Room& room)
{
    if( !(rooms_list -> room_exists(room.getNumber())) )
        throw RoomNotInSystemError("Tried to add a stay with unknown Room.", room);
}
