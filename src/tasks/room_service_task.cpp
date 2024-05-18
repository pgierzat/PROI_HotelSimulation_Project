#include "room_service_task.hpp"
#include "../utilities/errors.hpp"

RoomServiceTask::RoomServiceTask(const std::string& id, const Room& room, Dish dish) :
    SmallTask{id, "Bring a dish to a room."}, room{room}, dish{dish} {}

const Room& RoomServiceTask::get_room() const noexcept { return room; }

Dish RoomServiceTask::get_dish() const noexcept { return dish; }
