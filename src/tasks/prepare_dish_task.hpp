#ifndef PREPARE_DISH_TASK_HPP
#define PREPARE_DISH_TASK_HPP

#include "small_task.hpp"
#include "../workers/cook.hpp"
#include "../types/dish.hpp"


class PrepareDishTask : public SmallTask
{
    public:
        PrepareDishTask(const std::string& id, Dish);

        Dish get_dish() const noexcept;
        void assign(const Cook&);
        void unassign() noexcept override;
        const Cook& get_assignee() const override;
    protected:
        Dish dish;
        const Cook* assignee = nullptr;
};


#endif
