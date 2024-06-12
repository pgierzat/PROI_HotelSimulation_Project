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

StaySameRoomID::StaySameRoomID(const Room& room) noexcept : room_id{room.get_id()} {}
StaySameRoomID::StaySameRoomID(const std::string& room_id) noexcept : room_id{room_id} {}

bool StaySameRoomID::operator()(const InnerStay& stay) const noexcept {
    return stay.get_croom_observer().get_observed_id() == room_id;
}

bool StaySameRoomID::operator()(const std::unique_ptr<InnerStay>& stay) const noexcept {
    return stay -> get_croom_observer().get_observed_id() == room_id;
}


StayHasGuestID::StayHasGuestID(const Guest& guest) noexcept : guest_id{guest.get_id()} {}
StayHasGuestID::StayHasGuestID(const std::string& guest_id) noexcept : guest_id{guest_id} {}

bool StayHasGuestID::operator()(const InnerStay& stay) const noexcept
{
    return stay.get_cguests_observer().has_id(guest_id);
}

bool StayHasGuestID::operator()(const std::unique_ptr<InnerStay>& stay) const noexcept
{
    return stay -> get_cguests_observer().has_id(guest_id);
}
