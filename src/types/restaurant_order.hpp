#ifndef RESTAURANT_ORDER_HPP
#define RESTAURANT_ORDER_HPP
#include <string>
#include <vector>
#include "../types/dish.hpp"
#include "../types/amount.hpp"

class RestaurantOrder
{
    protected:
        std::vector<Dish> dishes;
        void addDish(Dish& dish);
    public:
        Amount get_price() const noexcept;
        const std::vector<Dish>& get_dishes();
};

#endif
