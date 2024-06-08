#ifndef PAYCHECK_SYSTEM_HPP
#define PAYCHECK_SYSTEM_HPP

#include "../workers/worker.hpp"
#include "../inner_types/inner_paycheck.hpp"
#include "../auxiliary/time_publisher.hpp"
#include "../auxiliary/time_observer.hpp"
#include "worker_system.hpp"
#include "timetable_system.hpp"
#include <chrono>

class HotelSystem;

class PaycheckSystem : public TimeObserver, public OtherSystemObserver<Worker>
{
    public:
        PaycheckSystem(TimePublisher&, WorkerSystem&, TimetableSystem&);
        PaycheckSystem(const PaycheckSystem&) = delete;
        std::vector<const Paycheck*> get_paychecks() const noexcept;
        void notify(const jed_utils::datetime&) override;
        void notify_realloc(dummy<Worker>);
        void notify_erase(const std::string& erased_obj_id, dummy<Worker>);
    private:
        void calculate_paychecks(std::chrono::year_month);
        WorkerSystem* w_system;
        const TimetableSystem* tt_system;
        jed_utils::datetime time;
        std::vector<InnerPaycheck> paychecks;
};

#endif
