#include "bring_dish_task.hpp"
#include "../utilities/errors.hpp"

const std::string BringDishTask::description = "Bring a dish to a table.";

BringDishTask::BringDishTask(const std::string& id, Dish dish, const std::string& table_nr) :
    Task{id}, SmallTask{id}, dish{dish}, table_nr{table_nr} {}

Dish BringDishTask::get_dish() const noexcept { return dish; }

const std::string& BringDishTask::get_table_nr() const noexcept { return table_nr; }

const std::string& BringDishTask::get_description() const noexcept { return description; }
