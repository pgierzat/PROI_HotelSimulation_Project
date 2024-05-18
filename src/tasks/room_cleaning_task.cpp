#include <algorithm>
#include "room_cleaning_task.hpp"
#include "../utilities/errors.hpp"

RoomCleaningTask::RoomCleaningTask(const std::string& id, const Room& room) :
    BigTask{id, "Clean a room.", room.calculatePersonel()}, room{room} {}

const Room& RoomCleaningTask::get_room() const noexcept { return room; }

void RoomCleaningTask::assign(const Maid& maid)
{
    can_assign(maid);
    if (++assigned == required)
        status = TaskStatus::assigned;
    assignees.push_back(&maid);
} 

void RoomCleaningTask::unassign() noexcept {
    assignees.clear();
    status = TaskStatus::unassigned;
}

const std::vector<const Maid*>& RoomCleaningTask::get_assignees() const noexcept { return assignees; }

std::vector<const Worker*> RoomCleaningTask::get_workers() const noexcept
{
    std::vector<const Worker*> workers{};
    std::ranges::for_each(assignees, [&](const Maid* maid){ workers.push_back(maid); });
    return workers;
}
