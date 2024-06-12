#ifndef SERVICE_SYSTEM_HPP
#define SERVICE_SYSTEM_HPP

#include "../services/service.hpp"
#include "../utilities/concepts.hpp"

class GuestSystem;
class WorkerSystem;
class RoomsList;
class StaySystem;
class TaskSystem;


class ServiceSystem :
    public OtherSystemObserver<Worker>,
    public OtherSystemObserver<Room>,
    public OtherSystemObserver<Guest>,
    public OtherSystemObserver<Stay>,
    public OtherSystemObserver<Task>
{
        using WS = WorkerSystem;
        using RL = RoomsList;
        using GS = GuestSystem;
        using SS = StaySystem;
        using TS = TaskSystem;
    public:
        ServiceSystem(GS&, WS&, RL&, SS&, TS&);
        std::optional<const Service*> find_by_id(const std::string& id) const noexcept;
        const Service& get_by_id(const std::string& id) const;
        template <SupportedService T>
            void add_service(const T&);
        SS& get_s_system() noexcept;
        TS& get_t_system() noexcept;
    private:
        std::vector<std::unique_ptr<Service>> services;
        WorkerSystem* w_system = nullptr;
        const RoomsList* rooms_list = nullptr;
        const GuestSystem* g_system = nullptr;
        StaySystem* s_system = nullptr;
        TaskSystem* t_system = nullptr;
};


template <SupportedService T>
void ServiceSystem::add_service(const T& service)
{

}

#endif
