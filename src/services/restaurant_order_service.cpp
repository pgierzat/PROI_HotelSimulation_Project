#include "restaurant_order_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"
#include "../tasks/prepare_dish_task.hpp"
#include "../tasks/bring_dish_task.hpp"
#include "../tasks/room_service_task.hpp"
#include "../types/table.hpp"
#include "restaurant_order.hpp"

const std::string RestaurantOrderService::description = "Order a meal for a guest.";


RestaurantOrderService::RestaurantOrderService(const std::string& id, const Guest& requestee, const jed_utils::datetime& time) :
    TaskService{id, requestee}, time{time} {}


RestaurantOrderService::RestaurantOrderService(const std::string& id, const Guest& requestee, const jed_utils::datetime& time, const Room& room) :
    TaskService{id, requestee}, time{time}, room{room}


void RestaurantOrderService::add_to_systems(ServiceSystem& sc_system)
{
    const auto& requestee = g_system -> get_by_id(requestee_id);
    for(auto dish : RestaurantOrder::order)
    {
        t_system -> add_task(PrepareDishTask(id, dish));
        preparedishtask_id = id;
        if(room == nullptr)
        {
            t_system -> add_task(BringDishTask(id, dish, table));
            bringdishtask_id = id;
        }else{
            t_system -> add_task(RoomServiceTask(id, room, dish));
            roomtask_id = id;
        }
    }
}

const std::string& RestaurantOrderService::get_description() const noexcept { return description; }

std::vector<const Task*> RestaurantOrderService::get_tasks() const
{
    return std::vector<const Task*>{&get_prepare_dish_task(), &get_bring_dish_task()};
}

const PrepareDishTask& RestaurantOrderService::get_prepare_dish_task() const
{
    return dynamic_cast<const PrepareDishTask&>(t_system -> get_by_id(preparedishtask_id));
}


const BringDishTask& RestaurantOrderService::get_bring_dish_task() const
{
    return dynamic_cast<const BringDishTask&>(t_system -> get_by_id(bringdishtask_id));
}

const RoomServiceTask& RestaurantOrderService::get_room_service_task() const
{
    return dynamic_cast<const RoomServiceTask&>(t_system -> get_by_id(roomtask_id));
}

Amount RestaurantOrderService::get_total_price() const noexcept { return Amount(RestaurantOrder::checkout_order()); }