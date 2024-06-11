#ifndef TASK_SYSTEM_HPP
#define TASK_SYSTEM_HPP

#include "worker_system.hpp"
#include "guest_system.hpp"
#include "../inner_types/concrete_inner_task.hpp"
#include "../auxiliary/other_system_observer.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../auxiliary/id_generator.hpp"
#include "../tasks/task.hpp"

class TaskSystem : public OtherSystemObserver<Worker>, public OtherSystemObserver<Room>, public OtherSystemObserver<Guest>
{
    public:
        TaskSystem(WorkerSystem&, RoomsList&, GuestSystem&);
        TaskSystem(const TaskSystem&) = delete;
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
        void notify_erase(const std::string& erased_id, dummy<Worker>) override;
        void notify_erase(const std::string& erased_id, dummy<Room>) override;
        void notify_erase(const std::string& erased_id, dummy<Guest>) override;
    private:
        static void check_task_status(const Task&);
        std::optional<Task*> find_task(const Task&) const noexcept;
        Task& get_task(const Task&) const;
        IDGenerator id_gen{};
        WorkerSystem* w_system;
        RoomsList* rooms_list;
        GuestSystem* g_system;
        std::vector<std::unique_ptr<InnerTask>> tasks;
};


template<SupportedTask T>
void TaskSystem::add_task(const T& task)
{
    check_task_status(task);
    if (find_by_id(task.Task::get_id()))
        throw DuplicateTaskIDError("Tried to add a duplicate task to TaskSystem.", task);
    auto to_add = std::make_unique<ConcreteInnerTask<T>>(task);
    tasks.emplace_back(std::move(to_add));
    auto& task_obj = *tasks.back();
    auto& wmosog = task_obj.get_wosog();
    auto& wmosor = task_obj.get_wosor();
    try {
        auto guest_id = wmosog.get_id();
        if (not guest_id.empty())
            wmosog.notify_realloc(g_system -> get_by_id(guest_id));
        auto room_id = wmosor.get_id();
        if (not room_id.empty())
            wmosor.notify_realloc(rooms_list -> get_by_id(room_id));
    } catch (const RoomNotInSystemError& e) {
        tasks.pop_back();
        throw e;
    } catch (const GuestNotInSystemError& e) {
        tasks.pop_back();
        throw e;
    }
    id_gen.forbid_id(task.Task::get_id());
}

template<SupportedTask T>
std::string TaskSystem::add_task_id(const T& task)
{
    auto task_to_add = task;
    auto new_id = id_gen.generate_id();
    task_to_add.set_id(new_id);
    add_task(task_to_add);
    return new_id;
}

template<SupportedTask T>
std::string TaskSystem::add_task_id(T&& task)
{
    auto new_id = id_gen.generate_id();
    task.set_id(new_id);
    add_task(task);
    return new_id;
}


#endif
