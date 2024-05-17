#ifndef PREPARE_DISH_TASK_HPP
#define PREPARE_DISH_TASK_HPP

#include "task.hpp"
#include "../workers/cook.hpp"

enum class Dish {
    PoachedEggs,
    ScrambledEggs,
    Omelette,
    FrenchToasts
};


class PrepareDishTask : public Task
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
