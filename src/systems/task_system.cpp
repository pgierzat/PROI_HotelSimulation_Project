#include <vector>
#include <algorithm>
#include "task_system.hpp"

void TaskSystem::bind_worker_system(WorkerSystem& w_system) noexcept
{ this -> w_system = &w_system; }

void TaskSystem::assign_task(const Task& task, const Worker& worker)
{
    auto& task_obj = validate_task(task);
    if (not get_w_system().has_worker(worker))
        throw WorkerNotInSystemError("Cannot assign task to an unknown worker.", worker);
    task_obj.assign(worker);
}

void TaskSystem::unassign_task(const Task& task)
{
    auto& task_obj = validate_task(task);
    task_obj.unassign();
}

void TaskSystem::complete_task(const Task& task)
{
    auto& task_obj = validate_task(task);
    task_obj.mark_completed();
}

std::optional<const Task*> TaskSystem::find_by_id(const std::string& id) const noexcept
{
    auto p = std::ranges::find_if(tasks, [&](const auto& otr_task){ return otr_task -> get_id() == id; });
    if (p == tasks.end())
        return std::nullopt;
    return &**p;
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

WorkerSystem& TaskSystem::get_w_system() const
{
    if (!w_system)
        throw SystemNotBoundError("WorkerSystem not bound to TaskSystem");
    return *w_system;
}

Task& TaskSystem::validate_task(const Task& task) const
{
    auto p = std::ranges::find_if(tasks, [&](const auto& otr_task){ return *otr_task == task; });
    if (p == tasks.end())
        throw TaskNotInSystemError("Unsuccesfull task validation", task);
    return **p;
}
