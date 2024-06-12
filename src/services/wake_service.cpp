#include "wake_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"


const std::string WakeService::description = "Wake guest(s) at a room. ";

WakeService::WakeService(const std::string& id, const Guest& requestee, const Room& room,
    const jed_utils::datetime& time) : TaskService{id, requestee}, RoomObs{room}, time{time} {}

void WakeService::add_to_systems(ServiceSystem& sc_system)
{
    auto& t_system = sc_system.get_t_system();
    auto& task = t_system.add_task_id(WakeTask("", RoomObs::get(), time));

}

const std::string& WakeService::get_description() const noexcept { return description; }

const WakeTask& WakeService::get_waketask() const
{
    return dynamic_cast<const WakeTask&>(*TasksObs::get().front());
}

Amount WakeService::get_default_price() const noexcept { return Amount{0, 0}; }