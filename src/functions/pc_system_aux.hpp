#ifndef PAYCHECK_SAME_WORKER_ID
#define PAYCHECK_SAME_WORKER_ID

#include "../types/paycheck.hpp"
#include <memory>


class PaycheckSameWorkerID
{
    public:
        PaycheckSameWorkerID(const Paycheck&);
        PaycheckSameWorkerID(const std::string& id);
        bool operator()(const Paycheck&);
    private:
        const std::string& id;
};

#endif
