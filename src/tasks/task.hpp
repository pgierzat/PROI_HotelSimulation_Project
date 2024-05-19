#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include "../workers/worker.hpp"

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
        const std::string& get_id() const noexcept;
        const std::string& get_description() const noexcept;
        TaskStatus get_status() const noexcept;
        void mark_completed();
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