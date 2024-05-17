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
        virtual void unassign() noexcept = 0;
        virtual const Worker& get_assignee() const = 0;
    protected:
        void can_assign(const Worker&);
        std::string id;
        std::string description;
        TaskStatus status{TaskStatus::unassigned};
};

#endif