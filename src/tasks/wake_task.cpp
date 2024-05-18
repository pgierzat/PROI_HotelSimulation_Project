#include "wake_task.hpp"
#include "../utilities/errors.hpp"

WakeTask::WakeTask(const std::string& id, const Room& room, const jed_utils::datetime& time) :
    Task{id, "Wake guest(s) at a room."}, room{room}, time{time} {}

const Room& WakeTask::get_room() const noexcept { return room; }

const jed_utils::datetime& WakeTask::get_time() const noexcept { return time; }

void WakeTask::assign(const Maid& maid)
{
    can_assign(maid);
    status = TaskStatus::assigned;
    assignee = &maid;
}

void WakeTask::unassign() noexcept
{
    assignee = nullptr;
    status = TaskStatus::unassigned;
}

const Maid& WakeTask::get_assignee() const
{
    if (not assignee)
        throw TaskStatusError("Tried to get the assignee of an unassigned task.", *this);
    return *assignee;
}
