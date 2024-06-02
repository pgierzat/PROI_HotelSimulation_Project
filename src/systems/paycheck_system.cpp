#include "hotel_system.hpp"
#include "../utilities/errors.hpp"
#include "../functions/tt_system_aux.hpp"
#include "../functions/vec_to_pvec.hpp"


PaycheckSystem::PaycheckSystem(WorkerSystem& w_system, TimetableSystem& tt_system) :
    w_system{&w_system}, tt_system{&tt_system}
{
    Paycheck::set_w_system(w_system);
}

// Time has to be set at least once a month. Every "bonus" that is assigned to worker between
// the start of a month and the moment of time set is included in previous month's paycheck.
// So it is best to synchonise all systems with the same time and process Tasks (assigning bonus attributes)
// after synchronising.
void PaycheckSystem::set_time(const jed_utils::datetime& time)
{
    if (time < this -> time)
        throw TurnBackTimeError("Tried to turn PaycheckSystem's time back.", time);
    this -> time = time;
    auto month = time.get_year_month();
    if (month != current_month)
    {
        calculate_paychecks();
        w_system -> reset_stats();
        current_month = month;
    }
}

const std::vector<Paycheck>& PaycheckSystem::get_paychecks() const noexcept { return paychecks; }

void PaycheckSystem::calculate_paychecks()
{
    paychecks.clear();
    auto all_entries = vec_to_pvec(tt_system -> get_entries());
    for (const Worker* worker : w_system -> get_workers())
    {
        auto prev_month = time.get_year_month() - std::chrono::months{1};
        unsigned hours = hours_worked(all_entries, *worker, prev_month);
        auto paycheck = worker -> calculate_paycheck(hours); 
        if (paycheck != Amount{0, 0})
            paychecks.emplace_back(*worker, paycheck);
    }
}
