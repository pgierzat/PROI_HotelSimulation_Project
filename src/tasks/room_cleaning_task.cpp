#include <algorithm>
#include "../systems/task_system.hpp"
#include "room_cleaning_task.hpp"
#include "../utilities/errors.hpp"

RoomCleaningTask::RoomCleaningTask(const std::string& id, const Room& room) :
    BigTask{id, "Clean a room.", room.calculatePersonel()}, room_nr{room.getNumber()} {}

const Room& RoomCleaningTask::get_room() const noexcept
{
    return rooms_list -> get_by_number(room_nr);
}
