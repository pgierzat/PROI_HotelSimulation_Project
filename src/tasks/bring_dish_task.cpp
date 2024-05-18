#include "bring_dish_task.hpp"
#include "../utilities/errors.hpp"

BringDishTask::BringDishTask(const std::string& id, Dish dish, const Table& table) :
    SmallTask{id, "Bring a dish to a table"}, dish{dish}, table{table} {}

Dish BringDishTask::get_dish() const noexcept { return dish; }

const Table& BringDishTask::get_table() const noexcept { return table; }

void BringDishTask::assign(const Waiter& waiter)
{
    can_assign(waiter);
    status = TaskStatus::assigned;
    assignee = &waiter;
} 

void BringDishTask::unassign() noexcept {
    assignee = nullptr;
    status = TaskStatus::unassigned;
}

const Waiter& BringDishTask::get_assignee() const
{
    if (not assignee)
        throw TaskStatusError("Tried to get the assignee of an unassigned task.", *this);
    return *assignee;
}
