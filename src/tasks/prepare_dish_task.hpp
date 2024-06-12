#ifndef PREPARE_DISH_TASK_HPP
#define PREPARE_DISH_TASK_HPP

#include "small_task.hpp"
#include "../auxiliary/pseudo_own_system_observer.hpp"
#include "../workers/cook.hpp"
#include "../types/dish.hpp"


class PrepareDishTask :
    public SmallTask<Cook>,
    protected PseudoOwnSystemObserver<Room>,
    protected PseudoOwnSystemObserver<Guest>
{
    public:
        PrepareDishTask(const std::string& id, Dish);
        Dish get_dish() const noexcept;
        const std::string& get_description() const noexcept override;
    protected:
        static const std::string description;
        Dish dish;
};


#endif
