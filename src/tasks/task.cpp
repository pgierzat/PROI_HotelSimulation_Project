#include "task.hpp"
#include "../utilities/errors.hpp"

Task::Task(const std::string& id, const std::string& description) :
    id{id}, description{description}, status{TaskStatus::unassigned} {}

const std::string& Task::get_id() const noexcept { return id; }

const std::string& Task::get_description() const noexcept { return description; }

TaskStatus Task::get_status() const noexcept { return status; }

void Task::mark_completed()
{
    if (status != TaskStatus::assigned)
        throw TaskStatusError("Task has to be assigned first before completion.", *this);
    this -> status = TaskStatus::completed;
}
