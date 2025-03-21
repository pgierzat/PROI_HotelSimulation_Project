#include "stay_system.hpp"
#include "guest_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../functions/vec_to_pvec.hpp"
#include "hotel_system.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/useful.hpp"
#include "../functions/has_elem.hpp"
#include "../functions/s_system_aux.hpp"
#include <ranges>
#include <optional>
#include <algorithm>

StaySystem::StaySystem(TimePublisher& t_publisher, GuestSystem& g_system, RoomsList& rooms_list) :
    time{t_publisher.get_time()}, g_system{&g_system}, rooms_list{&rooms_list}
{
    t_publisher.subscribe(*this);
    g_system.subscribe(*this);
    rooms_list.subscribe(*this);
}

void StaySystem::notify(const jed_utils::datetime& time)
{
    if (time < this -> time)
        throw TurnBackTimeError("Tried to turn StaySystem's time back.", time);
    this -> time = time;
}

const Stay& StaySystem::add_stay(const Stay& stay)
{
    if (time - stay.get_start() >= jed_utils::timespan(1))
        throw StayBackwardBookError("Tried to book a stay that starts on a past hotel nigth.", stay, time);
    if (stay.get_status() != StayStatus::booked)
        throw StayStatusError("Stay added to system must be in booked state.", stay);
    if (does_overlap(stay))
        throw StayOverlapError("Attempt to add overlapping stay.", stay);
    stays.emplace_back(std::make_unique<InnerStay>(stay));
    auto& stay_obj = *stays.back();
    OwnSystemObserver<Room>& room_observer = stay_obj.get_room_observer();
    MultipleOwnSystemObserver<Guest>& guests_observer = stay_obj.get_guests_observer();
    try {
        auto room_id = room_observer.get_observed_id();
        room_observer.notify_realloc(rooms_list -> get_by_id(room_id));
        for (auto guest_id : guests_observer.get_observed_ids())
            guests_observer.notify_realloc(g_system -> get_by_id(*guest_id));
    } catch (const RoomNotInSystemError& e) {
        stays.pop_back();
        throw e;
    } catch (const GuestNotInSystemError& e) {
        stays.pop_back();
        throw e;
    }
    stay_obj.set_status(StayStatus::booked);
    gen.forbid_id(stay.get_id());
    return *stays.back();
}

const Stay& StaySystem::add_stay_id(const Stay& stay)
{
    auto id = gen.generate_id();
    auto to_add = stay;
    to_add.set_id(id);
    return add_stay(to_add);
}

void StaySystem::remove_stay(const Stay& stay)
{
    auto id = stay.get_id();
    publish_erase(id);
    std::erase_if(stays, [&](const auto& otr){ return otr -> get_id() == id; });
}

std::optional<const Stay*> StaySystem::find_by_id(const std::string& id) const noexcept
{
    auto p = std::ranges::find_if(stays, [&](const auto& stay){ return stay -> get_id() == id; });
    if (p == stays.end())
        return std::nullopt;
    return &**p;
}

const Stay& StaySystem::get_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(stays, [&](const auto& stay){ return stay -> get_id() == id; });
    if (p == stays.end())
        throw StayNotInSystemError("get_by_id failed", id);
    return **p;
}

std::vector<const Stay*> StaySystem::get_stays() const noexcept
{
    return vec_to_pvec<InnerStay, Stay>(stays);
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
    if (time < stay.get_start() + Stay::checkin_time)
        throw StayStatusError("Tried to check-out a stay that hasn't yet started.", stay);
    get_stay(stay).set_status(StayStatus::checked_out);   // here, can impose fees for late check-out
}

std::optional<InnerStay*> StaySystem::find_stay(const Stay& stay) const noexcept
{
    auto p = std::ranges::find(stays, stay, [](const auto& otr_stay){ return *otr_stay; });
    if (p == stays.end())
        return std::nullopt;
    return const_cast<InnerStay*>(&**p);
}

InnerStay& StaySystem::get_stay(const Stay& stay) const
{
    auto stay_opt = find_stay(stay);
    if (not stay_opt)
        throw StayNotInSystemError("Cannot get stay", stay.get_id());
    return *stay_opt.value();
}

void StaySystem::notify_erase(const std::string& erased_obj_id, dummy<Room>)
{
    std::erase_if(stays, StaySameRoomID(erased_obj_id));
    // notify observers
}

void StaySystem::notify_erase(const std::string& erased_obj_id, dummy<Guest>)
{
    std::erase_if(stays, StayHasGuestID(erased_obj_id));
    // notify observers
}

bool StaySystem::does_overlap(const Stay& stay) const noexcept
{
    auto interval = stay.get_interval();
    auto same_room = StaySameRoomID(stay.get_room());
    auto room_stays = stays | std::views::filter([&](const auto& otr_stay){ return same_room(*otr_stay); });
    auto p = std::ranges::find_if(room_stays,
        [&](const auto& otr_stay){ return distance( interval, otr_stay -> get_interval() ) < jed_utils::timespan{0}; });
    return p != room_stays.end();
}

bool StaySystem::check_room(const Room& room) const
{
    return (rooms_list -> find_by_id(room.get_id())).has_value();
}
