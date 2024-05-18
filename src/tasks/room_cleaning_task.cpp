#include <algorithm>
#include "room_cleaning_task.hpp"
#include "../utilities/errors.hpp"

RoomCleaningTask::RoomCleaningTask(const std::string& id, const Room& room) :
    BigTask{id, "Clean a room.", room.calculatePersonel()}, room{room} {}

const Room& RoomCleaningTask::get_room() const noexcept { return room; }
