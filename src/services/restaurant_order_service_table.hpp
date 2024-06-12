#ifndef RESTAURANT_ORDER_SERVICE_TABLE
#define RESTAURANT_ORDER_SERVICE_TABLE

#include "restaurant_order_service.hpp"
#include "../tasks/bring_dish_task.hpp"


class RestaurantOrderServiceTable : public RestaurantOrderService
{
        using TasksObs = MultipleOwnSystemObserver<Task>;
    public:
        RestaurantOrderServiceTable(const std::string& id, const Guest& requestee,
            const RestaurantOrder&, const jed_utils::datetime& time,
            const std::string& table_nr);
        const std::string& get_description() const noexcept override;
        std::vector<const BringDishTask*> get_bring_dish_tasks() const;
    private:
        static const std::string description;
        std::string table_nr;
};


#endif
