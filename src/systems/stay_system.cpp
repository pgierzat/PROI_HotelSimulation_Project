#include "stay_system.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/useful.hpp"
#include "../functions/has_elem.hpp"
#include "../functions/s_system_aux.hpp"
#include <ranges>
#include <algorithm>

const jed_utils::timespan StaySystem::checkout_time = jed_utils::timespan{0, 10, 0, 0};

const jed_utils::timespan StaySystem::checkin_time = jed_utils::timespan{0, 16, 0, 0};

StaySystem::StaySystem(const GuestSystem& g_system, const RoomsList& rooms_list) :
    g_system{&g_system}, rooms_list{&rooms_list}
{
    Stay::set_s_system(*this);
    Stay::set_g_system(g_system);
    Stay::set_rooms_list(rooms_list);
}

const GuestSystem& StaySystem::get_cguest_system() const { return *g_system; }

const RoomsList& StaySystem::get_crooms_list() const { return *rooms_list; }

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
    if (stay.get_status() != StayStatus::booked)
        throw StayStatusError("Stay added to system must be in state: booked.", stay);
    if (stay.get_room().getCapacity() < stay.get_guests().size())
        throw RoomCapacityExceededError("Tried to add a stay with too many Guests.", stay);
    check_overlap(stay);
    stays.push_back(stay);
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

void StaySystem::check_in(const Stay& stay)
{
    if (check_regression(stay, StayStatus::checked_in) == RegressionStatus::equal)
        return;
    if (not is_in(time, stay.get_interval()))
        throw StayStatusError("Tried to check-in a stay not during that stay", stay);
    validate_stay(stay).set_status(StayStatus::checked_in);
}

void StaySystem::check_out(const Stay& stay)
{
    if (check_regression(stay, StayStatus::checked_out) == RegressionStatus::equal)
        return;
    if (stay.get_status() != StayStatus::checked_in)
        throw StayStatusError("Tried to check-out a stay that wasn't checked-in.", stay);
    if (time < stay.get_start() + checkin_time)
        throw StayStatusError("Tried to check-out a stay that hasn't yet started.", stay);
    validate_stay(stay).set_status(StayStatus::checked_out);   // here, can impose fees for late check-out
}

bool StaySystem::check_room(const Room& room) const noexcept
{
    for(auto stay : stays){
        if (stay.get_room() == room)
            return true;
    }
    return false;
}
std::optional<Stay*> StaySystem::get_stay(const Stay& stay) const noexcept
{
    auto p = std::ranges::find(stays, stay);
    if (p == stays.end())
        return std::nullopt;
    return const_cast<Stay*>(&*p);
}

Stay& StaySystem::validate_stay(const Stay& stay) const
{
    auto stay_opt = get_stay(stay);
    if (not stay_opt)
        throw StayNotInSystemError("Stay not found.", stay);
    return *stay_opt.value();
}

void StaySystem::check_overlap(const Stay& stay) const
{
    const auto& room = stay.get_room();
    auto interval = stay.get_interval();
    auto room_stays = std::ranges::filter_view(stays,
        [&](const auto& otr_stay){ return otr_stay.get_room() == room; });
    auto p = std::ranges::find_if(room_stays,
        [&](const auto& otr_stay){ return distance( interval, otr_stay.get_interval() ) < jed_utils::timespan{0}; });
    if ( p != room_stays.end() )
        throw StayOverlapError("Attempt to add overlapping stay.", *p, stay);
}
