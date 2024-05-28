#include "stay_service.hpp"
#include "../systems/stay_system.hpp"

const std::string StayService::description = "Stay Service.";

StaySystem* StayService::s_system = nullptr;

StayService::StayService(const std::string& id, const Stay& stay) :
    Service{id, stay.get_main_guest()}, stay_id{stay.get_id()} {}

Amount StayService::get_default_price() const noexcept
{
    const auto& stay = get_stay();
    const auto& room = stay.get_room();
    return room.calculatePrice() * stay.get_duration();
}

const Stay& StayService::get_stay() const noexcept
{
    return s_system -> get_by_id(stay_id);
}

const std::string& StayService::get_description() const noexcept { return description; }

ServiceStatus StayService::refresh_status(const ServiceSystem& sc_system)
{
    if (status >= ServiceStatus::completed)
        return status;
    StayStatus s_status = s_system -> get_by_id(stay_id).get_status();
    switch (s_status)
    {
        case StayStatus::booked:
            status = ServiceStatus::ordered;
            break;
        case StayStatus::checked_in:
            status = ServiceStatus::in_progress;
            break;
        case StayStatus::checked_out:
            status = ServiceStatus::completed;
            break;
        default:
            throw UnknownStayStatusError{"cannot refresh StayService's state.", s_status};
    }
    return status;
}

void StayService::add_to_systems(ServiceSystem& sc_system) {}

void StayService::set_s_system(StaySystem& s_system) { StayService::s_system = &s_system; }
