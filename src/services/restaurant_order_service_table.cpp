#include "restaurant_order_service_table.hpp"
#include <algorithm>

const std::string RestaurantOrderServiceTable::description = "Order, delivered to table.";


RestaurantOrderServiceTable::RestaurantOrderServiceTable(const std::string& id, const Guest& requestee,
            const RestaurantOrder& order, const jed_utils::datetime& time, const std::string& table_nr) :
        RestaurantOrderService{id, requestee, order, time}, table_nr{table_nr}
{
    std::ranges::for_each(order.get_dishes(),
        [&](auto dish){ TasksObs::add_observed(BringDishTask{"", dish, table_nr}); });
}

const std::string& RestaurantOrderServiceTable::get_description() const noexcept { return description; }

std::vector<const BringDishTask*> RestaurantOrderServiceTable::get_bring_dish_tasks() const
{
    auto bringtasks = std::vector<const BringDishTask*>{};
    for ( auto task : TasksObs::get())
    {
        auto casted_task = dynamic_cast<const BringDishTask*>(task);
        if (casted_task)
            bringtasks.push_back(casted_task);
    }
    return bringtasks;
}
