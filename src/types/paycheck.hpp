#include <iostream>
#include "amount.hpp"

#ifndef PAYCHECK_HPP
#define PAYCHECK_HPP

class Worker;

class WorkerSystem;

class Paycheck
{
    public:
        Paycheck(const Worker&, const Amount&);
        const Worker& get_worker() const;
        Amount get_amount() const noexcept;
        bool operator==(const Paycheck&) const;
        static void set_w_system(const WorkerSystem&);
    private:
        static const WorkerSystem* w_system;
        const std::string worker_id;
        Amount amount;
};

std::ostream& operator<<(std::ostream&, const Paycheck&);

#endif
