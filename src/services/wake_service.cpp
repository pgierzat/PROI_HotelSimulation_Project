#include "wake_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"


const std::string WakeService::description = "Wake guest(s) at a room. ";

WakeService::WakeService(const std::string& id, const Guest& requestee, const Room& room, const jed_utils::datetime& time)
    : TaskService{id, requestee}, room{&room}, time{time} {}

void WakeService::add_to_systems(ServiceSystem& sc_system)
{    
    waketask_id = t_system -> add_task_id(WakeTask("", *room, time));   // change to suit to WakeTask constructor
}

const std::string& WakeService::get_description() const noexcept { return description; }

const WakeTask& WakeService::get_waketask() const
{
    return dynamic_cast<const WakeTask&>(t_system -> get_by_id(waketask_id));
}

std::vector<const Task*> WakeService::get_tasks() const
{
    return std::vector<const Task*>{&get_waketask()};
}

Amount WakeService::get_default_price() const noexcept { return Amount{0, 0}; }