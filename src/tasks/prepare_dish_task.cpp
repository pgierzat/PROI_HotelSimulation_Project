#include "prepare_dish_task.hpp"
#include "../utilities/errors.hpp"

PrepareDishTask::PrepareDishTask(const std::string& id, Dish dish) : Task{id, "Prepare a dish"}, dish{dish} {}

Dish PrepareDishTask::get_dish() const noexcept { return dish; }

void PrepareDishTask::assign(const Cook& cook)
{
    can_assign(cook);
    status = TaskStatus::assigned;
    assignee = &cook;
} 

void PrepareDishTask::unassign() noexcept {
    assignee = nullptr;
    status = TaskStatus::unassigned;
}

const Cook& PrepareDishTask::get_assignee() const
{
    if (not assignee)
        throw TaskStatusError("Tried to get the assignee of an unassigned task.", *this);
    return *assignee;
}
