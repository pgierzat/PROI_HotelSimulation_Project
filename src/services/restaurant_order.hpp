#ifndef RESTAURANT_ORDER_HPP
#define RESTAURANT_ORDER_HPP
#include <string>
#include <vector>
#include "../types/dish.hpp"

class RestaurantOrder
{
    protected:
        std::vector<Dish> order;
        void addDish(Dish& dish);
    public:
        Amount checkout_order();
};
#endif