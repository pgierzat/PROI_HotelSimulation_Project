#include "service_system.hpp"
#include "../services/stay_service.hpp"
#include "../services/task_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/stay_system.hpp"
#include <algorithm>

TaskSystem* ServiceSystem::t_system = nullptr;
StaySystem* ServiceSystem::s_system = nullptr;

ServiceSystem::ServiceSystem(const GS& g_system, const WS& w_system,
    const RL& rooms_list, SS& s_system, TS& t_system)
{
    ServiceSystem::t_system = &t_system;
    ServiceSystem::s_system = &s_system;
    Service::set_g_system(g_system);
    StayService::set_s_system(s_system);
    TaskService::set_t_system(t_system);
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
