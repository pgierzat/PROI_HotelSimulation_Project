#ifndef PAYCHECK_SYSTEM_HPP
#define PAYCHECK_SYSTEM_HPP

#include "../workers/worker.hpp"
#include "../types/paycheck.hpp"
#include "worker_system.hpp"
#include "timetable_system.hpp"
#include <chrono>

class HotelSystem;

class PaycheckSystem
{
    public:
        PaycheckSystem(WorkerSystem&, TimetableSystem&);
        PaycheckSystem(const PaycheckSystem&) = delete;
        void set_time(const jed_utils::datetime&);
        const std::vector<Paycheck>& get_paychecks() const noexcept;
    private:
        void calculate_paychecks();
        WorkerSystem* w_system;
        const TimetableSystem* tt_system;
        std::vector<Paycheck> paychecks;
        jed_utils::datetime time{1970, 1, 1};
        std::chrono::year_month current_month{time.get_year_month()};
};

#endif
