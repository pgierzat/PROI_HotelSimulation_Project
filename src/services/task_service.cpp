#include "task_service.hpp"
#include "../systems/task_system.hpp"


TaskSystem* TaskService::t_system = nullptr;

TaskService::TaskService(const std::string& id, const Guest& requestee) :
    Service{id, requestee} {}

ServiceStatus TaskService::refresh_status(const ServiceSystem& sc_system) noexcept
{
    if (status >= ServiceStatus::completed)
        return status;
    status = ServiceStatus::completed;
    for (auto task : get_tasks())
    {
        if (status == ServiceStatus::completed)
        {
            if (task -> get_status() == TaskStatus::assigned)
                status = ServiceStatus::in_progress;
            else if (task -> get_status() == TaskStatus::unassigned)
            {
                status = ServiceStatus::ordered;
                break;
            }
        }
        else
        {
            if (task -> get_status() == TaskStatus::unassigned)
            {
                status = ServiceStatus::ordered;
                break;
            }
        }
    }
    return status;
}

void TaskService::set_t_system(TaskSystem& t_system) { TaskService::t_system = &t_system; }
