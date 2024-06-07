#ifndef INNER_PAYCHECK_HPP
#define INNER_PAYCHECK_HPP

#include "../types/paycheck.hpp"
#include "../auxiliary/own_system_observer.hpp"
#include <vector>


class InnePaycheck : public Paycheck
{
    public:
        InnePaycheck(const Paycheck&);
        OwnSystemObserver<Worker>& get_worker_observer() noexcept;
        const OwnSystemObserver<Worker>& get_cworker_observer() const noexcept;
};

#endif
