#ifndef RESTAURANT_ORDER_SERVICE_HPP
#define RESTAURANT_ORDER_SERVICE_HPP

#include "restaurant_order.hpp"
#include "../tasks/prepare_dish_task.hpp"
#include "../tasks/bring_dish_task.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"
#include "../types/table.hpp"
#include "../types/datetime.h"
#include "task_service.hpp"

class RestaurantOrderService : public TaskService
{
    private:
        RestaurantOrder order;
        jed_utils::datetime time;
        std::string table_nr;
        const Room* room = nullptr;
        std::string prepdish_id="";
        std::string bringtask_id="";
        std::string roomservice_id="";
    public:
        RestaurantOrderService(const std::string& id, const Guest& requestee,
            const jed_utils::datetime& time, const std::string& table_nr);
        RestaurantOrderService(const std::string& id, const Guest& requestee,
            const jed_utils::datetime& time, const Room&); // constructor overload for room service
        void add_to_systems(ServiceSystem&) override;
        const std::string& get_description() const noexcept override;
        std::vector<const Task*> get_tasks() const;
        const PrepareDishTask& get_prepare_dish_task() const;
        const BringDishTask& get_bring_dish_task() const;
        const RoomServiceTask& get_room_service_task() const;
        Amount get_total_price() const noexcept;
        static const std::string description;
};
#endif