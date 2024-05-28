#include "task.hpp"
#include "../systems/task_system.hpp"
#include "../utilities/errors.hpp"

const WorkerSystem* Task::w_system = nullptr;
const RoomsList* Task::rooms_list = nullptr;
const GuestSystem* Task::g_system = nullptr;

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

void Task::set_w_system(const WorkerSystem& t_system) { Task::w_system = &t_system; }
void Task::set_rooms_list(const RoomsList& rooms_list) { Task::rooms_list = &rooms_list; }
void Task::set_g_system(const GuestSystem& g_system) { Task::g_system = &g_system; }

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
