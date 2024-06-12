#ifndef BRING_DISH_TASK_HPP
#define BRING_DISH_TASK_HPP

#include "small_task.hpp"
#include "../auxiliary/pseudo_own_system_observer.hpp"
#include "../workers/waiter.hpp"
#include "../types/restaurant_order.hpp"
#include "../types/table.hpp"


class BringDishTask :
    public SmallTask<Waiter>,
    protected PseudoOwnSystemObserver<Room>,
    protected PseudoOwnSystemObserver<Guest>
{
    public:
        BringDishTask(const std::string& id, Dish, const std::string& table_nr);
        Dish get_dish() const noexcept;
        const std::string& get_table_nr() const noexcept;
        const std::string& get_description() const noexcept override;
    protected:
        static const std::string description;
        Dish dish;
        std::string table_nr;
};


#endif
