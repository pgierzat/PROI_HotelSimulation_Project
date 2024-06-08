#ifndef PAYCHECK_SAME_WORKER_ID
#define PAYCHECK_SAME_WORKER_ID

#include "../inner_types/inner_paycheck.hpp"
#include <memory>


class PaycheckSameWorkerID
{
    public:
        PaycheckSameWorkerID(const Paycheck&);
        PaycheckSameWorkerID(const std::string& id);
        bool operator()(const InnerPaycheck&);
    private:
        const std::string& id;
};

#endif
