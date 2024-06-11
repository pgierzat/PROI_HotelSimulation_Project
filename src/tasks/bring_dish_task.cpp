#include "bring_dish_task.hpp"
#include "../utilities/errors.hpp"

BringDishTask::BringDishTask(const std::string& id, Dish dish, const std::string& table_nr) :
    SmallTask{id, "Bring a dish to a table."}, dish{dish}, table_nr{table_nr} {}

Dish BringDishTask::get_dish() const noexcept { return dish; }

const std::string& BringDishTask::get_table_nr() const noexcept { return table_nr; }
