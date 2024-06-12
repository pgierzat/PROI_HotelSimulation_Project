#include <vector>
#include <algorithm>
#include "task_system.hpp"
#include "../functions/has_elem.hpp"
#include "../auxiliary/t_system_aux.hpp"
#include "../tasks/bring_dish_task.hpp"
#include "../tasks/prepare_dish_task.hpp"
#include "../tasks/room_cleaning_task.hpp"
#include "../tasks/room_service_task.hpp"
#include "../tasks/taxi_task.hpp"
#include "../tasks/wake_task.hpp"

TaskSystem::TaskSystem(WorkerSystem& w_system, RoomsList& rooms_list, GuestSystem& g_system) :
    w_system{&w_system}, rooms_list{&rooms_list}, g_system{&g_system}
{
    w_system.subscribe(*this);
    rooms_list.subscribe(*this);
    g_system.subscribe(*this);
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

const Task& TaskSystem::add_task(const Task& task)
{
    auto proposition = dynamic_cast<const BringDishTask*>(&task);
    if (proposition) {
        add_task(*proposition);
        return;
    }
    auto proposition = dynamic_cast<const PrepareDishTask*>(&task);
    if (proposition) {
        add_task(*proposition);
        return;
    }
    auto proposition = dynamic_cast<const RoomCleaningTask*>(&task);
    if (proposition) {
        add_task(*proposition);
        return;
    }
    auto proposition = dynamic_cast<const RoomServiceTask*>(&task);
    if (proposition) {
        add_task(*proposition);
        return;
    }
    auto proposition = dynamic_cast<const TaxiTask*>(&task);
    if (proposition) {
        add_task(*proposition);
        return;
    }
    auto proposition = dynamic_cast<const WakeTask*>(&task);
    if (proposition) {
        add_task(*proposition);
        return;
    }
    throw UnsupportedTaskTypeError("Tried to add task of unsupported type", task);
}

void TaskSystem::remove_task(const Task& task) noexcept
{
    auto id_to_erase = task.get_id();
    publish_erase(id_to_erase);
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

void TaskSystem::notify_erase(const std::string& erased_id, dummy<Worker>) {
    auto pred = TaskSameWorker(erased_id);
    std::erase_if(tasks, [&](const auto& task){ return pred(*task); });
}

void TaskSystem::notify_erase(const std::string& erased_id, dummy<Room>) {
    auto pred = TaskSameRoom(erased_id);
    std::erase_if(tasks, [&](const auto& task){ return pred(*task); });
}

void TaskSystem::notify_erase(const std::string& erased_id, dummy<Guest>) {
    auto pred = TaskSameGuest(erased_id);
    std::erase_if(tasks, [&](const auto& task){ return pred(*task); });
}

void TaskSystem::check_task_status(const Task& task)
{
    if (task.get_status() != TaskStatus::unassigned)
        throw TaskStatusError("Can only add unassigned tasks to TaskSystem.", task);
}
