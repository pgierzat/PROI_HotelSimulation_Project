#ifndef WAKE_TASK_HPP
#define WAKE_TASK_HPP

#include "small_task.hpp"
#include "../rooms/hpp/room.hpp"
#include "../types/datetime.h"
#include "../workers/maid.hpp"

class WakeTask : public SmallTask
{
    public:
        WakeTask(const std::string& id, const Room&, const jed_utils::datetime&);
        const Room& get_room() const noexcept;
        const jed_utils::datetime& get_time() const noexcept;
        void assign(const Maid&);
        void unassign() noexcept override;
        const Maid& get_assignee() const override;
    protected:
        const Room& room;
        jed_utils::datetime time;
        const Maid* assignee = nullptr;
};

#endif
