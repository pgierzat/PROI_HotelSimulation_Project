#include "restaurant_order_service_room.hpp"
#include "../tasks/room_service_task.hpp"

const std::string RestaurantOrderServiceRoom::description = "Order, delivered to room.";


RestaurantOrderServiceRoom::RestaurantOrderServiceRoom(const std::string& id, const Guest& requestee,
            const RestaurantOrder& order, const jed_utils::datetime& time, const Room& room) :
        RestaurantOrderService{id, requestee, order, time}, RoomObs{room}
{
    std::ranges::for_each(order.get_dishes(),
        [&](auto dish){ TasksObs::add_observed(RoomServiceTask{"", room, dish}); });
}

const std::string& RestaurantOrderServiceRoom::get_description() const noexcept { return description; }

std::vector<const RoomServiceTask*> RestaurantOrderServiceRoom::get_room_service_tasks() const
{
    auto roomservicetasks = std::vector<const RoomServiceTask*>{};
    for ( auto task : TasksObs::get())
    {
        auto casted_task = dynamic_cast<const RoomServiceTask*>(task);
        if (casted_task)
            roomservicetasks.push_back(casted_task);
    }
    return roomservicetasks;
}
