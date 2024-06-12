#ifndef RESTAURANT_ORDER_SERVICE_ROOM_HPP
#define RESTAURANT_ORDER_SERVICE_ROOM_HPP

#include "restaurant_order_service.hpp"

class RestaurantOrderServiceRoom : public RestaurantOrderService, protected OwnSystemObserver<Room>
{
        using RoomObs = OwnSystemObserver<Room>;
        using TasksObs = MultipleOwnSystemObserver<Task>;
    public:
        RestaurantOrderServiceRoom(const std::string& id, const Guest& requestee,
            const RestaurantOrder&, const jed_utils::datetime& time, const Room&);
        const std::string& get_description() const noexcept override;
        std::vector<const RoomServiceTask*> get_room_service_tasks() const;
        static const std::string description;
};


#endif
