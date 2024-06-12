#ifndef RESTAURANT_ORDER_SERVICE_HPP
#define RESTAURANT_ORDER_SERVICE_HPP

#include "../types/restaurant_order.hpp"
#include "../tasks/prepare_dish_task.hpp"
#include "../tasks/bring_dish_task.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"
#include "../types/table.hpp"
#include "../types/datetime.h"
#include "task_service.hpp"

class RestaurantOrderService : public TaskService
{
        using TasksObs = MultipleOwnSystemObserver<Task>;
    public:
        RestaurantOrderService(const std::string& id, const Guest& requestee,
            const RestaurantOrder&, const jed_utils::datetime& time);
        std::vector<const PrepareDishTask*> get_prepare_dish_tasks() const;
        Amount get_default_price() const noexcept override;
    protected:
        RestaurantOrder order;
        jed_utils::datetime time;
};
#endif