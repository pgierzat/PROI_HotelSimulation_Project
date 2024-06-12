#include "restaurant_order_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"
#include "../tasks/prepare_dish_task.hpp"
#include "../tasks/bring_dish_task.hpp"
#include "../tasks/room_service_task.hpp"
#include "../types/table.hpp"
#include "../types/restaurant_order.hpp"


RestaurantOrderService::RestaurantOrderService(const std::string& id, const Guest& requestee,
    const RestaurantOrder& order, const jed_utils::datetime& time) :
        TaskService{id, requestee}, order{order}, time{time}
{
    std::ranges::for_each(order.get_dishes(),
        [&](const auto& dish){ TasksObs::add_observed(PrepareDishTask{"", dish}); });
}

std::vector<const PrepareDishTask*> RestaurantOrderService::get_prepare_dish_tasks() const
{
    auto preptasks = std::vector<const PrepareDishTask*>{};
    for ( auto task : TasksObs::get())
    {
        auto casted_task = dynamic_cast<const PrepareDishTask*>(task);
        if (casted_task)
            preptasks.push_back(casted_task);  
    }
    return preptasks;
}

Amount RestaurantOrderService::get_default_price() const noexcept { return order.get_price(); }
