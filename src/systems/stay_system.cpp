#include "stay_system.hpp"
#include "guest_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "hotel_system.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/useful.hpp"
#include "../functions/has_elem.hpp"
#include "../functions/s_system_aux.hpp"
#include <ranges>
#include <algorithm>

const jed_utils::timespan StaySystem::checkout_time = jed_utils::timespan{0, 10, 0, 0};

const jed_utils::timespan StaySystem::checkin_time = jed_utils::timespan{0, 16, 0, 0};

StaySystem::StaySystem(GuestSystem& g_system, RoomsList& rooms_list) :
    g_system{&g_system}, rooms_list{&rooms_list}
{
    g_system.subscribe(*this);
    rooms_list.subscribe(*this);
}

void StaySystem::set_time(const jed_utils::datetime& time)
{
    if (time < this -> time)
        throw TurnBackTimeError("Tried to turn StaySystem's time back.", time);
    this -> time = time;
}

void StaySystem::add_stay(const Stay& stay)
{
    if (time - stay.get_start() >= jed_utils::timespan(1))
        throw StayBackwardBookError("Tried to book a stay that starts on a past hotel nigth.", stay, time);
    if (stay.get_status() != StayStatus::initial)
        throw StayStatusError("Stay added to system must be in initial state.", stay);
    if (not rooms_list -> find_by_id(stay.get_room_id()))
        throw RoomNotInSystemError("Tried to add a Stay with unknown Room to StaySystem",
                                   stay.get_room_id());
    if (not g_system -> find_by_id(stay.get_main_guest_id()))
        throw GuestNotInSystemError("Tried to add a Stay with unknown Guest to StaySystem",
                                    stay.get_main_guest_id());
    check_overlap(stay);
    stays.push_back(stay);
    auto& stay_obj = stays.back();
    stay_obj.get_room_observer().notify_realloc(rooms_list -> get_by_id(stay.get_room_id()));
    auto& main_guest_id = stay.get_main_guest_id();
    stay_obj.get_guest_observer(main_guest_id).notify_realloc(g_system -> get_by_id(main_guest_id));
    stay_obj.set_status(StayStatus::booked);
}

void StaySystem::remove_stay(const Stay& stay) { std::erase(stays, stay); }

std::optional<const Stay*> StaySystem::find_by_id(const std::string& id) const noexcept
{
    auto p = std::ranges::find_if(stays, [&](const auto& stay){ return stay.get_id() == id; });
    if (p == stays.end())
        return std::nullopt;
    return &*p;
}

const Stay& StaySystem::get_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(stays, [&](const auto& stay){ return stay.get_id() == id; });
    if (p == stays.end())
        throw StayNotInSystemError("get_by_id failed", id);
    return *p;
}

const std::vector<Stay>& StaySystem::get_stays() const noexcept { return stays; }

void StaySystem::add_guest_to_stay(const Stay& stay, const Guest& guest)
{
    if (not g_system -> find_by_id(guest.get_id()))
        throw GuestNotInSystemError("Tried to add an unknown Guest to a Stay", guest);
    auto& stay_obj = get_stay(stay);
    stay_obj.add_guest(guest);
    const auto& id = guest.get_id();
    stay_obj.get_guest_observer(id).notify_realloc(g_system -> get_by_id(id));
}

void StaySystem::check_in(const Stay& stay)
{
    if (check_regression(stay, StayStatus::checked_in) == RegressionStatus::equal)
        return;
    if (not is_in(time, stay.get_interval()))
        throw StayStatusError("Tried to check-in a stay not during that stay", stay);
    get_stay(stay).set_status(StayStatus::checked_in);
}

void StaySystem::check_out(const Stay& stay)
{
    if (check_regression(stay, StayStatus::checked_out) == RegressionStatus::equal)
        return;
    if (stay.get_status() != StayStatus::checked_in)
        throw StayStatusError("Tried to check-out a stay that wasn't checked-in.", stay);
    if (time < stay.get_start() + checkin_time)
        throw StayStatusError("Tried to check-out a stay that hasn't yet started.", stay);
    get_stay(stay).set_status(StayStatus::checked_out);   // here, can impose fees for late check-out 
}

std::optional<Stay*> StaySystem::find_stay(const Stay& stay) const noexcept
{
    auto p = std::ranges::find(stays, stay);
    if (p == stays.end())
        return std::nullopt;
    return const_cast<Stay*>(&*p);
}

Stay& StaySystem::get_stay(const Stay& stay) const
{
    auto stay_opt = find_stay(stay);
    if (not stay_opt)
        throw StayNotInSystemError("Cannot get stay", stay.get_id());
    return *stay_opt.value();
}

void StaySystem::check_overlap(const Stay& stay) const
{
    auto interval = stay.get_interval();
    auto room_stays = stays | std::views::filter(StaySameRoom(stay.get_room_id()));
    auto p = std::ranges::find_if(room_stays,
        [&](const auto& otr_stay){ return distance( interval, otr_stay.get_interval() ) < jed_utils::timespan{0}; });
    if ( p != room_stays.end() )
        throw StayOverlapError("Attempt to add overlapping stay.", *p, stay);
}

void StaySystem::notify_realloc(dummy<Room>)
{
    for(auto& stay : stays)
    {
        auto& id = stay.get_room_observer().get_observed_id();
        const auto& new_obj = rooms_list -> get_by_id(id);
        stay.get_room_observer().notify_realloc(new_obj);
    }
        
}

void StaySystem::notify_erase(const std::string& erased_obj_id, dummy<Room>)
{
    std::erase_if(stays, StaySameRoom(erased_obj_id));
    // notify observers
}

void StaySystem::notify_realloc(dummy<Guest>)
{
    for(auto& stay : stays) {
        for (auto& obs : stay.get_guest_observers()) {
            auto& id = obs -> get_observed_id();
            const auto& new_obj = g_system -> get_by_id(id);
            obs -> notify_realloc(new_obj);
        }
    }
}

void StaySystem::notify_erase(const std::string& erased_obj_id, dummy<Guest>)
{
    std::erase_if(stays, StayHasGuest(erased_obj_id));
    // notify observers
}

bool StaySystem::check_room(const Room& room) const
{
    return (rooms_list -> find_by_id(room.get_id())).has_value();
}
