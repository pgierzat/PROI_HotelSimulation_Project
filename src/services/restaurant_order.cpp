#include "restaurant_order.hpp"
#include "../types/amount.hpp"
#include "../types/dish.hpp"
#include <algorithm>
void RestaurantOrder::addDish(Dish& dish)
{
    order.push_back(dish);
}

Amount RestaurantOrder::checkout_order()
{
    Amount total_price{0, 0};
    for(auto dish : order)
    {
        total_price += Amount(20, 0);
    }
    return total_price;
}