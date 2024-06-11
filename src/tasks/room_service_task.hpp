#ifndef ROOM_SERVICE_TASK_HPP
#define ROOM_SERVICE_TASK_HPP

#include "small_task.hpp"
#include "../auxiliary/pseudo_own_system_observer.hpp"
#include "../rooms/hpp/room.hpp"
#include "../types/datetime.h"
#include "../types/dish.hpp"
#include "../rooms/hpp/room.hpp"
#include "../workers/waiter.hpp"

class RoomServiceTask :
    public SmallTask<Waiter>,
    protected OwnSystemObserver<Room>,
    protected PseudoOwnSystemObserver<Guest>
{
        using RoomObs = OwnSystemObserver<Room>;
    public:
        RoomServiceTask(const std::string& id, const Room&, Dish);
        const Room& get_room() const noexcept;
        Dish get_dish() const noexcept;
        const std::string& get_description() const noexcept override;
    protected:
        static const std::string description;
        Dish dish;
};

#endif
