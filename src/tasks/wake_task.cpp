#include "wake_task.hpp"
#include "../utilities/errors.hpp"

WakeTask::WakeTask(const std::string& id, const Room& room, const jed_utils::datetime& time) :
    SmallTask{id, "Wake guest(s) at a room."}, room{room}, time{time} {}

const Room& WakeTask::get_room() const noexcept { return room; }

const jed_utils::datetime& WakeTask::get_time() const noexcept { return time; }
