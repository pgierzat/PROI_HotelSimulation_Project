#include "task.hpp"
#include "../systems/task_system.hpp"
#include "../utilities/errors.hpp"


Task::Task(const std::string& id, const std::string& description) :
    id{id}, description{description}, status{TaskStatus::unassigned} {}

const std::string& Task::get_id() const noexcept { return id; }

const std::string& Task::get_description() const noexcept { return description; }

TaskStatus Task::get_status() const noexcept { return status; }

void Task::set_id(const std::string& id) noexcept { this -> id = id; }

void Task::mark_completed()
{
    if (status != TaskStatus::assigned)
        throw TaskStatusError("Task has to be assigned first before completion.", *this);
    this -> status = TaskStatus::completed;
}

void Task::can_assign(const Worker& worker) const
{
    if (status == TaskStatus::completed)
        throw TaskAssignmentError{"Tried to assign worker to a completed task", *this, worker};
}

void Task::can_unassign() const
{
    if (status == TaskStatus::completed)
        throw TaskStatusError("Tried to unassign a completed Task.", *this);
}
