#include "service_system.hpp"
#include "../services/stay_service.hpp"
#include "../services/task_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/stay_system.hpp"
#include <algorithm>


ServiceSystem::ServiceSystem(WS& w_system, RL& rooms_list, GS& g_system, SS& s_system, TS& t_system) :
    w_system{&w_system}, rooms_list{&rooms_list}, g_system{&g_system}, 
    s_system{&s_system}, t_system{&t_system}
{
    w_system.subscribe(*this);
    rooms_list.subscribe(*this);
    g_system.subscribe(*this);
    s_system.subscribe(*this);
    t_system.subscribe(*this);
}

std::optional<const Service*> ServiceSystem::find_by_id(const std::string& id) const noexcept
{
    auto p = std::ranges::find_if(services, [&](const auto& service){ return service -> get_id() == id; });
    if (p == services.end())
        return std::nullopt;
    return p -> get();
}

const Service& ServiceSystem::get_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(services, [&](const auto& service){ return service -> get_id() == id; });
    if (p == services.end())
        throw ServiceNotInSystemError("ServiceSystem::get_by_id failed", id);
    return **p;
}

StaySystem& ServiceSystem::get_s_system() noexcept { return *s_system; }
TaskSystem& ServiceSystem::get_t_system() noexcept { return *t_system; }

void ServiceSystem::notify_erase(const std::string&, dummy<Worker>) {}
void ServiceSystem::notify_erase(const std::string&, dummy<Room>) {}
void ServiceSystem::notify_erase(const std::string&, dummy<Guest>) {}
void ServiceSystem::notify_erase(const std::string&, dummy<Stay>) {}
void ServiceSystem::notify_erase(const std::string&, dummy<Task>) {}
