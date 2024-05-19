#include "paycheck_system.hpp"
#include "../utilities/errors.hpp"


void PaycheckSystem::bind_worker_system(WorkerSystem& w_system) { this -> w_system = &w_system; }

void PaycheckSystem::bind_timetable_system(TimetableSystem& tt_system) { this -> tt_system = &tt_system; }

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
        close_month();
        current_month = month;
    }
}

const std::vector<Paycheck>& PaycheckSystem::get_paychecks() const noexcept { return paychecks; }

void PaycheckSystem::close_month() { get_w_system().reset_stats(); }

WorkerSystem& PaycheckSystem::get_w_system() const
{
    if (not w_system)
        throw SystemNotBoundError("WorkerSystem not bound to PaycheckSystem.");
    return *w_system;
}

TimetableSystem& PaycheckSystem::get_tt_system() const
{
    if (not tt_system)
        throw SystemNotBoundError("WorkerSystem not bound to PaycheckSystem.");
    return *tt_system;
}

void PaycheckSystem::calculate_paychecks()
{
    paychecks.clear();
    for (const Worker* worker : get_w_system().get_workers())
    {
        auto all_entries = get_tt_system().worker_entries(*worker);
        auto prev_month = time.get_year_month() - std::chrono::months{1};
        auto entries = month_entries(all_entries, prev_month);
        unsigned hours_worked = (worker -> get_shift_duration() * entries.size()).get_hours();
        if (hours_worked != 0)
            paychecks.emplace_back(*worker, worker -> calculate_paycheck(hours_worked));
    }
}
