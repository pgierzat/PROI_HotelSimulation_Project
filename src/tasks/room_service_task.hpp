#ifndef ROOM_SERVICE_TASK_HPP
#define ROOM_SERVICE_TASK_HPP

#include "small_task.hpp"
#include "../rooms/hpp/room.hpp"
#include "../types/datetime.h"
#include "../types/dish.hpp"
#include "../rooms/hpp/room.hpp"
#include "../workers/waiter.hpp"

class RoomServiceTask : public SmallTask<Waiter>
{
    public:
        RoomServiceTask(const std::string& id, const Room&, Dish);
        const Room& get_room() const noexcept;
        Dish get_dish() const noexcept;
    protected:
        const Room& room;
        Dish dish;
};

#endif
