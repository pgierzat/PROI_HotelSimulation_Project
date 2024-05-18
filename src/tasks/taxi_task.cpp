#include "taxi_task.hpp"
#include "../utilities/errors.hpp"

TaxiTask::TaxiTask(const std::string& id, const Guest& room, const jed_utils::datetime& time) :
    SmallTask{id, "Order a taxi for a guest."}, guest{room}, time{time} {}

const Guest& TaxiTask::get_guest() const noexcept { return guest; }

const jed_utils::datetime& TaxiTask::get_time() const noexcept { return time; }

void TaxiTask::assign(const Receptionist& receptionist)
{
    can_assign(receptionist);
    status = TaskStatus::assigned;
    assignee = &receptionist;
}

void TaxiTask::unassign() noexcept
{
    assignee = nullptr;
    status = TaskStatus::unassigned;
}

const Receptionist& TaxiTask::get_assignee() const
{
    if (not assignee)
        throw TaskStatusError("Tried to get the assignee of an unassigned task.", *this);
    return *assignee;
}
