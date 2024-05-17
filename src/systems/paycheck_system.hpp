#ifndef PAYCHECK_SYSTEM_HPP
#define PAYCHECK_SYSTEM_HPP

#include "../workers/worker.hpp"
#include "../types/paycheck.hpp"
#include "worker_system.hpp"
#include "timetable_system.hpp"
#include <chrono>

class PaycheckSystem
{
    public:
        PaycheckSystem() = default;
        void bind_worker_system(WorkerSystem&);
        void bind_timetable_system(TimetableSystem&);
        void set_time(const jed_utils::datetime&);
        const std::vector<Paycheck>& get_paychecks() const noexcept;
    private:
        void calculate_paychecks();
        void close_month();
        WorkerSystem* w_system = nullptr;
        TimetableSystem* tt_system = nullptr;
        std::vector<Paycheck> paychecks;
        jed_utils::datetime time{1970, 1, 1};
        std::chrono::year_month current_month{time.get_year_month()};
};

#endif
