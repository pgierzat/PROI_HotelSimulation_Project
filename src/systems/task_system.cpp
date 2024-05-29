#include <vector>
#include <algorithm>
#include "task_system.hpp"
#include "../functions/has_elem.hpp"

TaskSystem::TaskSystem(WorkerSystem& w_system, RoomsList& rooms_list, GuestSystem& g_system) :
    w_system{&w_system}
{
    Task::set_w_system(w_system);
    Task::set_rooms_list(rooms_list);
    Task::set_g_system(g_system);
}

void TaskSystem::assign_task(const Task& task, const Worker& worker)
{
    if (!has_elem_ptr(w_system -> get_workers(), worker))
        throw WorkerNotInSystemError("Cannot assign task to an unknown worker.", worker);
    validate_task(task).assign(worker);
}

void TaskSystem::unassign_task(const Task& task) { validate_task(task).unassign(); }

void TaskSystem::complete_task(const Task& task) { validate_task(task).mark_completed(); }

std::optional<const Task*> TaskSystem::find_by_id(const std::string& id) const noexcept
{
    auto p = std::ranges::find_if(tasks, [&](const auto& otr_task){ return otr_task -> get_id() == id; });
    if (p == tasks.end())
        return std::nullopt;
    return &**p;
}

const Task& TaskSystem::get_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(tasks, [&](const auto& otr_task){ return otr_task -> get_id() == id; });
    if (p == tasks.end())
        throw TaskNotInSystemError("TaskSystem::get_by_id failed", id);
    return **p;
}

void TaskSystem::remove_task(const Task& task) noexcept
{
    std::erase_if(tasks, [&](const auto& ptr){ return *ptr == task; });
}

std::vector<const Task*> TaskSystem::get_tasks() const noexcept
{
    std::vector<const Task*> tasks_cp{};
    std::ranges::for_each(tasks, [&](const auto& ptr){ tasks_cp.push_back(&*ptr); });
    return tasks_cp;
}

Task& TaskSystem::validate_task(const Task& task) const
{
    auto p = std::ranges::find_if(tasks, [&](const auto& otr_task){ return *otr_task == task; });
    if (p == tasks.end())
        throw TaskNotInSystemError("Unsuccesfull task validation", task);
    return **p;
}

void TaskSystem::check_task_status(const Task& task)
{
    if (task.get_status() != TaskStatus::unassigned)
        throw TaskStatusError("Can only add unassigned tasks to TaskSystem.", task);
}
