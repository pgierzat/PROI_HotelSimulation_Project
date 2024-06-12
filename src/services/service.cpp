#include "service.hpp"
#include "../systems/guest_system.hpp"
#include "../utilities/errors.hpp"


Service::Service(const std::string& id, const Guest& requestee) :
    OSO{requestee}, id{id} {}

const std::string& Service::get_id() const noexcept { return id; }
const Guest& Service::get_requestee() const noexcept { OSO::get(); }
const Amount& Service::get_price() const noexcept { return price; }
ServiceStatus Service::get_status() const noexcept { return status; }
void Service::set_price(const Amount& price) { this -> price = price; }

void Service::mark_paid_for()
{
    if (status < ServiceStatus::completed)
        throw ServiceStatusError("Uncompleted Service cannot be marked as 'paid for'.", *this);
    status = ServiceStatus::paid_for;
}

