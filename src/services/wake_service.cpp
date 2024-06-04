#include "wake_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"


const std::string WakeService::description = "Wake guest(s) at a room.";

WakeService::WakeService(const std::string& id, const Room&, const jed_utils::datetime& time) :
    TaskService{id, }