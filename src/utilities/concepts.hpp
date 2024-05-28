#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <concepts>

class Cook;
class Maid;
class Receptionist;
class Waiter;

template<typename T>
concept SupportedWorker =
    std::same_as<T, Cook> ||
    std::same_as<T, Maid> ||
    std::same_as<T, Receptionist> ||
    std::same_as<T, Waiter>;

class BringDishTask;
class PrepareDishTask;
class RoomCleaningTask;
class RoomServiceTask;
class TaxiTask;
class WakeTask;

template<typename T>
concept SupportedTask = 
    std::same_as<T, BringDishTask> ||
    std::same_as<T, PrepareDishTask> ||
    std::same_as<T, RoomCleaningTask> ||
    std::same_as<T, RoomServiceTask> ||
    std::same_as<T, TaxiTask> ||
    std::same_as<T, WakeTask>;

class StayService;
class TaxiService;
class RoomService;
class ExtraRoomCleaningService;
class WakeService;
class RestaurantOrderService;

template<typename T>
concept SupportedService = 
    std::same_as<T, StayService> ||
    std::same_as<T, TaxiService> ||
    std::same_as<T, RoomService> ||
    std::same_as<T, ExtraRoomCleaningService> ||
    std::same_as<T, WakeService> ||
    std::same_as<T, RestaurantOrderService>;


#endif
