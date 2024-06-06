#include "s_system_aux.hpp"
#include "../utilities/errors.hpp"

RegressionStatus check_regression(const Stay& stay, StayStatus new_status)
{
    auto prev_status = stay.get_status();
    if (new_status < prev_status)
        throw StayStatusError("Tried to reverse stay's progress.", stay);
    if (new_status == prev_status)
        return RegressionStatus::equal;
    return RegressionStatus::progression;
}

StaySameRoom::StaySameRoom(const Room& room) noexcept : room_id{room.get_id()} {}
StaySameRoom::StaySameRoom(const std::string& room_id) noexcept : room_id{room_id} {}

bool StaySameRoom::operator()(const Stay& stay) const noexcept {
    return stay.get_room_id() == room_id;
}

bool StaySameRoom::operator()(const std::unique_ptr<Stay>& stay) const noexcept {
    return stay -> get_room_id() == room_id;
}


StayHasGuest::StayHasGuest(const Guest& guest) noexcept : guest_id{guest.get_id()} {}
StayHasGuest::StayHasGuest(const std::string& guest_id) noexcept : guest_id{guest_id} {}

bool StayHasGuest::operator()(const Stay& stay) const noexcept
{
    auto ids = stay.get_guest_ids();
    auto p = std::ranges::find(ids, guest_id, [](auto ptr){ return *ptr; });
    return p != ids.end();
}

bool StayHasGuest::operator()(const std::unique_ptr<Stay>& stay) const noexcept
{
    auto ids = stay -> get_guest_ids();
    auto p = std::ranges::find(ids, guest_id, [](auto ptr){ return *ptr; });
    return p != ids.end();
}
