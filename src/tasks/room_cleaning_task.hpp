#ifndef PREPARE_DISH_TASK_HPP
#define PREPARE_DISH_TASK_HPP

#include <vector>
#include "big_task.hpp"
#include "../workers/maid.hpp"
#include "../rooms/hpp/room.hpp"


class RoomCleaningTask : public BigTask
{
    public:
        RoomCleaningTask(const std::string& id, const Room&);

        const Room& get_room() const noexcept;
        void assign(const Maid&);
        void unassign() noexcept override;
        const std::vector<const Maid*>& get_assignees() const noexcept;
        std::vector<const Worker*> get_workers() const noexcept override;
    protected:
        const Room& room;
        std::vector<const Maid*> assignees;
};


#endif
