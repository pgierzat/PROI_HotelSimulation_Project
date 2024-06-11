#include <algorithm>
#include "../systems/task_system.hpp"
#include "room_cleaning_task.hpp"
#include "../utilities/errors.hpp"

RoomCleaningTask::RoomCleaningTask(const std::string& id, const Room& room) :
    BigTask{id, "Clean a room.", room.calculatePersonel()}, RoomObs{room} {}

const Room& RoomCleaningTask::get_room() const noexcept { return RoomObs::get(); }

void RoomCleaningTask::set_room(const Room& room) noexcept { RoomObs::set(room); }
