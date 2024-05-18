#ifndef BIG_TASK_HPP
#define BIG_TASK_HPP

#include <vector>
#include "task.hpp"

class BigTask : public Task
{
    protected:
        BigTask(const std::string& id, const std::string& description, unsigned workers_required);
        virtual void can_assign(const Worker&) const override;
        unsigned required;
        unsigned assigned = 0;
    public:
        unsigned get_required() const noexcept;
        unsigned get_assigned() const noexcept;
        virtual std::vector<const Worker*> get_workers() const noexcept = 0;
};

#endif
