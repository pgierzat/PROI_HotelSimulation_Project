#include "service_system.hpp"
#include "../services/stay_service.hpp"
#include "../services/task_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/stay_system.hpp"
#include <algorithm>


ServiceSystem::ServiceSystem(GS& g_system, WS& w_system, RL& rooms_list, SS& s_system, TS& t_system) :
    g_system{&g_system}, w_system{&w_system}, rooms_list{&rooms_list},
    s_system{&s_system}, t_system{&t_system}
{
    g_system.subscribe(*this);
    w_system.subscribe(*this);
    rooms_list.subscribe(*this);
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
