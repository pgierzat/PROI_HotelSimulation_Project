#include "stay_service.hpp"
#include "../systems/stay_system.hpp"

const std::string StayService::description = "Stay Service.";

StayService::StayService(const std::string& id, const Stay& stay) :
    Service{id, stay.get_main_guest()}, OSO{stay}
{
    price = get_default_price();
}

Amount StayService::get_default_price() const noexcept
{
    const auto& stay = OSO::get();
    const auto& room = stay.get_room();
    return room.calculatePrice() * stay.get_duration();
}

const Stay& StayService::get_stay() const noexcept { return OSO::get(); }

const std::string& StayService::get_description() const noexcept { return description; }

void StayService::add_to_systems(ServiceSystem& sc_system) {}
