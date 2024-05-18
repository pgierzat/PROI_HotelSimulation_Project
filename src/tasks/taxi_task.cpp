#include "taxi_task.hpp"
#include "../utilities/errors.hpp"

TaxiTask::TaxiTask(const std::string& id, const Guest& room, const jed_utils::datetime& time) :
    SmallTask{id, "Order a taxi for a guest."}, guest{room}, time{time} {}

const Guest& TaxiTask::get_guest() const noexcept { return guest; }

const jed_utils::datetime& TaxiTask::get_time() const noexcept { return time; }
