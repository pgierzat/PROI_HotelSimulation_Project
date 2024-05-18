#include "bring_dish_task.hpp"
#include "../utilities/errors.hpp"

BringDishTask::BringDishTask(const std::string& id, Dish dish, const Table& table) :
    SmallTask{id, "Bring a dish to a table."}, dish{dish}, table{table} {}

Dish BringDishTask::get_dish() const noexcept { return dish; }

const Table& BringDishTask::get_table() const noexcept { return table; }
