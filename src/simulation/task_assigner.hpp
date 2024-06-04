#ifndef TASK_ASSIGNER_HPP
#define TASK_ASSIGNER_HPP

#include "../systems/hotel_system.hpp"
#include "../systems/task_system.hpp"
#include "../systems/worker_system.hpp"

class TaskAssigner
{
    public:
        TaskAssigner(HotelSystem&);
    private:
        TaskSystem* t_system;
        const WorkerSystem* w_system;
};


#endif
