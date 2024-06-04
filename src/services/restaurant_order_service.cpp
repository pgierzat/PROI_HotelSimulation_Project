#include "restaurant_order_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"
#include "../tasks/prepare_dish_task.hpp"
#include "../tasks/bring_dish_task.hpp"
#include "../tasks/room_service_task.hpp"
#include "../types/table.hpp"
#include "restaurant_order.hpp"

const std::string RestaurantOrderService::description = "Order a meal for a guest.";


RestaurantOrderService::RestaurantOrderService(const std::string& id, const Guest& requestee,
    const jed_utils::datetime& time, const Table& table) :
        TaskService{id, requestee}, time{time}, table{&table} {}


RestaurantOrderService::RestaurantOrderService(const std::string& id, const Guest& requestee,
    const jed_utils::datetime& time, const Room& room) :
        TaskService{id, requestee}, time{time}, room{&room} {}


void RestaurantOrderService::add_to_systems(ServiceSystem& sc_system)
{
    for(auto dish : order.get_dishes())
    {
        prepdish_id = t_system -> add_task_id(PrepareDishTask("", dish));
        if (not room)
            bringtask_id = t_system -> add_task_id(BringDishTask(id, dish, *table));
        else
            roomservice_id = t_system -> add_task_id(RoomServiceTask(id, *room, dish));
    }
}

const std::string& RestaurantOrderService::get_description() const noexcept { return description; }

std::vector<const Task*> RestaurantOrderService::get_tasks() const
{
    return std::vector<const Task*>{&get_prepare_dish_task(), &get_bring_dish_task()};
}

const PrepareDishTask& RestaurantOrderService::get_prepare_dish_task() const
{
    return dynamic_cast<const PrepareDishTask&>(t_system -> get_by_id(prepdish_id));
}


const BringDishTask& RestaurantOrderService::get_bring_dish_task() const
{
    return dynamic_cast<const BringDishTask&>(t_system -> get_by_id(bringtask_id));
}

const RoomServiceTask& RestaurantOrderService::get_room_service_task() const
{
    return dynamic_cast<const RoomServiceTask&>(t_system -> get_by_id(roomservice_id));
}

Amount RestaurantOrderService::get_total_price() const noexcept { return order.get_price(); }
