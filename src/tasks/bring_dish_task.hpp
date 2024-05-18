#ifndef BRING_DISH_TASK_HPP
#define BRING_DISH_TASK_HPP

#include "small_task.hpp"
#include "../workers/waiter.hpp"
#include "../types/dish.hpp"
#include "../types/table.hpp"


class BringDishTask : public SmallTask<Waiter>
{
    public:
        BringDishTask(const std::string& id, Dish, const Table&);
        Dish get_dish() const noexcept;
        const Table& get_table() const noexcept;
    protected:
        Dish dish;
        const Table& table;
};


#endif
