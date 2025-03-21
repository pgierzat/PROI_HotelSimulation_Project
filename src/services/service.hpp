#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <string>
#include <vector>
#include "../auxiliary/own_system_observer.hpp"
#include "../types/guest.hpp"
#include "../types/amount.hpp"
#include "../tasks/task.hpp"

enum class ServiceStatus {
    ordered,
    in_progress,   // it means e.g. all TaskService's Tasks are assigned, what's left is to wait
    completed,
    paid_for
};

class ServiceSystem;

class Service : protected OwnSystemObserver<Guest>
{
        using GuestObs = OwnSystemObserver<Guest>;
    public:
        virtual ~Service() = default;
        const std::string& get_id() const noexcept;
        const Guest& get_requestee() const noexcept;
        const Amount& get_price() const noexcept;
        void set_price(const Amount&);
        virtual Amount get_default_price() const noexcept= 0;
        ServiceStatus get_status() const noexcept;
        void mark_paid_for();
        virtual const std::string& get_description() const noexcept = 0;
        virtual void add_to_systems(ServiceSystem&) = 0;
        virtual bool operator==(const Service&) const;
    protected:
        enum class ServiceAdded {
            added,
            not_added
        };
        Service(const std::string& id, const Guest& requestee);
        std::string id;
        Amount price;
        ServiceStatus status{ServiceStatus::ordered};
        ServiceAdded added{ServiceAdded::not_added};
};

#endif
