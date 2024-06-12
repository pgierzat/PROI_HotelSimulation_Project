#include "task_service.hpp"
#include "../systems/task_system.hpp"


TaskService::TaskService(const std::string& id, const Guest& requestee) :
    Service{id, requestee}, TasksObs{} {}

std::vector<const Task*> TaskService::get_tasks() const { return TasksObs::get(); }
