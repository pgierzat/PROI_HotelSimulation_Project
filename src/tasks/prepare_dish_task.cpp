#include "prepare_dish_task.hpp"
#include "../utilities/errors.hpp"


const std::string PrepareDishTask::description = "Bring a dish to a table.";

PrepareDishTask::PrepareDishTask(const std::string& id, Dish dish) :
    Task{id}, SmallTask{id}, dish{dish} {}

Dish PrepareDishTask::get_dish() const noexcept { return dish; }

const std::string& PrepareDishTask::get_description() const noexcept { return description; }
