#ifndef PAYCHECK_SYSTEM_HPP
#define PAYCHECK_SYSTEM_HPP

#include "../workers/worker.hpp"
#include "../paycheck.hpp"
#include "worker_system.hpp"

class PaycheckSystem
{
    public:
        PaycheckSystem() = default;
        PaycheckSystem(const PaycheckSystem&) = delete;
        PaycheckSystem(PaycheckSystem&&) = delete;
        PaycheckSystem& operator=(const PaycheckSystem&) = delete;
        PaycheckSystem& operator=(PaycheckSystem&&) = delete;

        void bind_worker_system(WorkerSystem&);
        void close_month();
        std::vector<Paycheck> calculate_paychecks();
    private:
        WorkerSystem* worker_system = nullptr;
};

#endif
