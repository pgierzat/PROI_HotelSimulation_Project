#include "taxi_task.hpp"
#include "../utilities/errors.hpp"


const std::string TaxiTask::description = "Order a taxi for a guest.";

TaxiTask::TaxiTask(const std::string& id, const Guest& room, const jed_utils::datetime& time) :
    Task{id}, SmallTask{id}, GuestObs{room}, time{time} {}

const Guest& TaxiTask::get_guest() const noexcept { return GuestObs::get(); }

const jed_utils::datetime& TaxiTask::get_time() const noexcept { return time; }

void TaxiTask::set_guest(const Guest& guest) noexcept { GuestObs::set(guest); }

void TaxiTask::set_time(const jed_utils::datetime& time) noexcept { this -> time = time; }

const std::string& TaxiTask::get_description() const noexcept { return description; }
