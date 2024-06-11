#include <vector>
#include <algorithm>
#include "task_system.hpp"
#include "../functions/has_elem.hpp"

TaskSystem::TaskSystem(WorkerSystem& w_system, RoomsList& rooms_list, GuestSystem& g_system) :
    w_system{&w_system}
{
}

void TaskSystem::assign_task(const Task& task, const Worker& worker)
{
    if (not w_system -> find_by_id(worker.get_id()))
        throw WorkerNotInSystemError("Cannot assign task to an unknown worker.", worker);
    get_task(task).assign(worker);
}

void TaskSystem::unassign_task(const Task& task) { get_task(task).unassign(); }

void TaskSystem::complete_task(const Task& task) { get_task(task).mark_completed(); }

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
    auto id_to_erase = task.get_id();
    std::erase_if(tasks, [&](const auto& ptr){ return ptr -> get_id() == id_to_erase; });
}

std::vector<const Task*> TaskSystem::get_tasks() const noexcept
{
    std::vector<const Task*> tasks_cp{};
    std::ranges::for_each(tasks, [&](const auto& ptr){ tasks_cp.push_back(ptr.get()); });
    return tasks_cp;
}

std::optional<Task*> TaskSystem::find_task(const Task& task) const noexcept
{
    auto p = std::ranges::find_if(tasks,
        [&](const auto& otr_task){ return otr_task -> get_id() == task.get_id(); });
    if (p == tasks.end())
        return std::nullopt;
    return p -> get();
}

Task& TaskSystem::get_task(const Task& task) const
{
    auto p = std::ranges::find_if(tasks,
        [&](const auto& otr_task){ return otr_task -> get_id() == task.get_id(); });
    if (p == tasks.end())
        throw TaskNotInSystemError("Unsuccesfull task validation", task);
    return **p;
}

void TaskSystem::check_task_status(const Task& task)
{
    if (task.get_status() != TaskStatus::unassigned)
        throw TaskStatusError("Can only add unassigned tasks to TaskSystem.", task);
}
