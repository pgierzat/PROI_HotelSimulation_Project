#include <algorithm>
#include "../systems/task_system.hpp"
#include "room_cleaning_task.hpp"
#include "../utilities/errors.hpp"


const std::string RoomCleaningTask::description = "Clean a room.";

RoomCleaningTask::RoomCleaningTask(const std::string& id, const Room& room) :
    Task{id}, BigTask{id, room.calculatePersonel()}, RoomObs{room} {}

const Room& RoomCleaningTask::get_room() const noexcept { return RoomObs::get(); }

void RoomCleaningTask::set_room(const Room& room) noexcept { RoomObs::set(room); }

const std::string& RoomCleaningTask::get_description() const noexcept { return description; }
