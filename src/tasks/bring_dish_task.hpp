#ifndef BRING_DISH_TASK_HPP
#define BRING_DISH_TASK_HPP

#include "task.hpp"
#include "../workers/waiter.hpp"
#include "../types/dish.hpp"
#include "../types/table.hpp"


class BringDishTask : public Task
{
    public:
        BringDishTask(const std::string& id, Dish, const Table&);

        Dish get_dish() const noexcept;
        const Table& get_table() const noexcept;
        void assign(const Waiter&);
        void unassign() noexcept override;
        const Waiter& get_assignee() const override;
    protected:
        Dish dish;
        const Table& table;
        const Waiter* assignee = nullptr;
};


#endif
