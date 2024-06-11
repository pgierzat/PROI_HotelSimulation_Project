#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include "../workers/worker.hpp"
#include "../systems/worker_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../systems/guest_system.hpp"
#include "../auxiliary/weak_own_system_observer.hpp"
#include "../auxiliary/own_system_observer.hpp"

enum class TaskStatus {
    unassigned,
    assigned,
    completed
};


class Task
{
    protected:
        Task(const std::string& id, const std::string& description);
    public:
        virtual ~Task() = default;
        const std::string& get_id() const noexcept;
        const std::string& get_description() const noexcept;
        TaskStatus get_status() const noexcept;
        void mark_completed();
        void set_id(const std::string&) noexcept;
        virtual void assign(const Worker&) = 0;
        virtual void unassign() = 0;
        bool operator==(const Task&) const = default;
    protected:
        virtual void can_assign(const Worker&) const;
        virtual void can_unassign() const;
        std::string id;
        std::string description;
        TaskStatus status{TaskStatus::unassigned};
};

#endif