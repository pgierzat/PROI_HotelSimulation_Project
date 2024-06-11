#ifndef SERVICE_SYSTEM_HPP
#define SERVICE_SYSTEM_HPP

#include "../services/service.hpp"
#include "../utilities/concepts.hpp"

class GuestSystem;
class WorkerSystem;
class RoomsList;
class StaySystem;
class TaskSystem;


class ServiceSystem
{
        using GS = GuestSystem;
        using WS = WorkerSystem;
        using RL = RoomsList;
        using SS = StaySystem;
        using TS = TaskSystem;
    public:
        ServiceSystem(const GS&, const WS&, const RL&, SS&, TS&);
        ServiceSystem(const ServiceSystem&) = delete;
        std::optional<const Service*> find_by_id(const std::string& id) const noexcept;
        const Service& get_by_id(const std::string& id) const;
        template <SupportedService T>
            void add_service(const T&);
    private:
        std::vector<std::unique_ptr<Service>> services;
        static TaskSystem* t_system;
        static StaySystem* s_system;
};


template <SupportedService T>
void ServiceSystem::add_service(const T& service)
{

}

#endif
