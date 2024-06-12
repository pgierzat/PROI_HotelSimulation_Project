#include "task_service.hpp"
#include "../systems/task_system.hpp"


TaskService::TaskService(const std::string& id, const Guest& requestee) :
    Service{id, requestee}, TasksObs{} {}

std::vector<const Task*> TaskService::get_tasks() const { return TasksObs::get(); }

void TaskService::add_to_systems(ServiceSystem& sc_system)
{
    if (added == ServiceAdded::added)
        throw ServiceStatusError("Tried to add service to systems twice.", *this);
    auto& t_system = sc_system.get_t_system();
    for(const auto& task : TasksObs::get())
    {
        auto& added = t_system.add_task(*task);
        TasksObs::notify_realloc(added);
    }
}
