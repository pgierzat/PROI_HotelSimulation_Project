#ifndef TASK_SYSTEM_HPP
#define TASK_SYSTEM_HPP

#include "worker_system.hpp"
#include "guest_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../tasks/task.hpp"

class TaskSystem
{
    public:
        TaskSystem(WorkerSystem&, RoomsList&, GuestSystem&);
        void assign_task(const Task&, const Worker&);
        void unassign_task(const Task&);
        void complete_task(const Task&);
        std::optional<const Task*> find_by_id(const std::string& id) const noexcept;
        const Task& get_by_id(const std::string& id) const;
        template<SupportedTask T>
            void add_task(const T&);
        void remove_task(const Task&) noexcept;
        std::vector<const Task*> get_tasks() const noexcept;
        bool operator==(const TaskSystem&) const = default;
    private:
        Task& validate_task(const Task&) const;
        WorkerSystem* w_system;
        RoomsList* rooms_list;
        GuestSystem* g_system;
        std::vector<std::unique_ptr<Task>> tasks;
};


template<SupportedTask T>
void TaskSystem::add_task(const T& task)
{
    if (task.get_status() != TaskStatus::unassigned)
        throw TaskStatusError("Can only add unassigned tasks to TaskSystem.", task);
    auto task_opt = find_by_id(task.get_id());
    if (task_opt)
        throw DuplicateTaskIDError("Tried to add a duplicate task to TaskSystem.", task);
    tasks.push_back(std::move(std::make_unique<T>(task)));
}


#endif
