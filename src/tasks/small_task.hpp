#ifndef SMALL_TASK_HPP
#define SMALL_TASK_HPP

#include "task.hpp"

class SmallTask : public Task
{
    protected:
        SmallTask(const std::string& id, const std::string& description);
    public:
        virtual const Worker& get_assignee() const = 0;
};

#endif
