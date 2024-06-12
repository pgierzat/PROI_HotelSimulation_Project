#include "restaurant_order.hpp"
#include "../types/amount.hpp"
#include "../types/dish.hpp"
#include <algorithm>
void RestaurantOrder::addDish(Dish& dish)
{
    dishes.push_back(dish);
}

Amount RestaurantOrder::get_price() const noexcept
{
    return Amount{20, 0} * dishes.size();
}

const std::vector<Dish>& RestaurantOrder::get_dishes() const noexcept { return dishes; }
