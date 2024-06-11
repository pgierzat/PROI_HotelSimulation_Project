#include "wake_task.hpp"
#include "../utilities/errors.hpp"

WakeTask::WakeTask(const std::string& id, const Room& room, const jed_utils::datetime& time) :
    SmallTask{id, "Wake guest(s) at a room."}, RoomObs{room}, time{time} {}

const Room& WakeTask::get_room() const noexcept { return RoomObs::get(); }

const jed_utils::datetime& WakeTask::get_time() const noexcept { return time; }

void WakeTask::set_room(const Room& room) noexcept { RoomObs::set(room); }

void WakeTask::set_time(const jed_utils::datetime& time) noexcept { this -> time = time; }
