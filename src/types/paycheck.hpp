#include <iostream>
#include "amount.hpp"
#include "../auxiliary/own_system_observer.hpp"

#ifndef PAYCHECK_HPP
#define PAYCHECK_HPP

class Worker;

class Paycheck
{
    public:
        Paycheck(const Worker&, const Amount&);
        const Worker& get_worker() const;
        const std::string& get_worker_id() const;
        Amount get_amount() const noexcept;
        bool operator==(const Paycheck&) const;
        OwnSystemObserver<Worker>& get_w_observer() noexcept;
    private:
        OwnSystemObserver<Worker> w_observer;
        Amount amount;
};

std::ostream& operator<<(std::ostream&, const Paycheck&);

#endif
