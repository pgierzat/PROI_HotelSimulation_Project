#ifndef TASK_SYSTEM_HPP
#define TASK_SYSTEM_HPP

#include "worker_system.hpp"
#include "guest_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../auxiliary/id_generator.hpp"
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
        template<SupportedTask T>
            std::string add_task_id(const T&);
        template<SupportedTask T>
            std::string add_task_id(T&&);
        void remove_task(const Task&) noexcept;
        std::vector<const Task*> get_tasks() const noexcept;
        bool operator==(const TaskSystem&) const = default;
    private:
        static void check_task_status(const Task&);
        Task& validate_task(const Task&) const;
        IDGenerator id_gen{};
        WorkerSystem* w_system;
        RoomsList* rooms_list;
        GuestSystem* g_system;
        std::vector<std::unique_ptr<Task>> tasks;
};


template<SupportedTask T>
void TaskSystem::add_task(const T& task)
{
    check_task_status(task);
    auto task_opt = find_by_id(task.get_id());
    if (task_opt)
        throw DuplicateTaskIDError("Tried to add a duplicate task to TaskSystem.", task);
    id_gen.forbid_id(task.get_id());
    tasks.push_back(std::move(std::make_unique<T>(task)));
}

template<SupportedTask T>
std::string TaskSystem::add_task_id(const T& task)
{
    check_task_status(task);
    auto task_to_add = task;
    auto new_id = id_gen.generate_id();
    task_to_add.set_id(new_id);
    tasks.push_back(std::move(std::make_unique<T>(task_to_add)));
    return new_id;
}

template<SupportedTask T>
std::string TaskSystem::add_task_id(T&& task)
{
    check_task_status(task);
    auto new_id = id_gen.generate_id();
    task.set_id(new_id);
    tasks.push_back(std::move(std::make_unique<T>(task)));
    return new_id;
}



#endif
