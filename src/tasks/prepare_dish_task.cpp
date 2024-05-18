#include "prepare_dish_task.hpp"
#include "../utilities/errors.hpp"

PrepareDishTask::PrepareDishTask(const std::string& id, Dish dish) : SmallTask{id, "Prepare a dish."}, dish{dish} {}

Dish PrepareDishTask::get_dish() const noexcept { return dish; }

