#include "hotel_system.hpp"
#include "../utilities/errors.hpp"
#include "../functions/tt_system_aux.hpp"
#include "../functions/vec_to_pvec.hpp"
#include "../functions/pc_system_aux.hpp"


PaycheckSystem::PaycheckSystem(TimePublisher& publisher, WorkerSystem& w_system, TimetableSystem& tt_system) :
    w_system{&w_system}, tt_system{&tt_system}, time{publisher.get_time()}
{
    w_system.subscribe(*this);
    publisher.subscribe(*this);
}

std::vector<const Paycheck*> PaycheckSystem::get_paychecks() const noexcept
{
    return vec_to_pvec<InnerPaycheck, Paycheck>(paychecks);
}

void PaycheckSystem::calculate_paychecks(std::chrono::year_month month)
{
    paychecks.clear();
    auto all_entries = tt_system -> get_entries();
    for (const Worker* worker : w_system -> get_workers())
    {
        unsigned hours = hours_worked(all_entries, *worker, month);
        auto paycheck = worker -> calculate_paycheck(hours); 
        if (paycheck != Amount{0, 0})
<<<<<<< HEAD
            paychecks.emplace_back(*worker, paycheck);
=======
        {
            paychecks.emplace_back(*worker, paycheck);
            
        }
            
>>>>>>> main
    }
}

// Time has to be set at least once a month. Every "bonus" that is assigned to worker between
// the start of a month and the moment of time set is included in previous month's paycheck.
// So it is best to synchonise all systems with the same time and process Tasks (assigning bonus attributes)
// after synchronising.
void PaycheckSystem::notify(const jed_utils::datetime& time)
{
    if (time < this -> time)
        throw TurnBackTimeError("Tried to turn PaycheckSystem's time back.", time);
    auto curr_month = time.get_year_month();
    auto prev_month = (this -> time).get_year_month();
    if (curr_month != prev_month)
    {
        calculate_paychecks(prev_month);
        w_system -> reset_stats();
    }
    this -> time = time;
}

void PaycheckSystem::notify_realloc(dummy<Worker>)
{
    for(auto& paycheck : paychecks)
    {
        auto& worker_observer = paycheck.get_worker_observer();
        auto& id = worker_observer.get_id();
        const auto& new_obj = w_system -> get_by_id(id);
        worker_observer.notify_realloc(new_obj);
    }  
}

void PaycheckSystem::notify_erase(const std::string& erased_obj_id, dummy<Worker>)
{
    std::erase_if(paychecks, PaycheckSameWorkerID(erased_obj_id));
}
