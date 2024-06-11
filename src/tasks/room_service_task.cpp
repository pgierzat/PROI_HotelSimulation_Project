#include "room_service_task.hpp"
#include "../utilities/errors.hpp"


const std::string RoomServiceTask::description = "Bring a dish to a room.";

RoomServiceTask::RoomServiceTask(const std::string& id, const Room& room, Dish dish) :
    Task{id}, SmallTask{id}, room{room}, dish{dish} {}

const Room& RoomServiceTask::get_room() const noexcept { return room; }

Dish RoomServiceTask::get_dish() const noexcept { return dish; }

const std::string& RoomServiceTask::get_description() const noexcept { return description; }
