#include <iostream>
#include "amount.hpp"

#ifndef PAYCHECK_HPP
#define PAYCHECK_HPP

class Worker;

class Paycheck
{
    public:
        Paycheck(const Worker&, const Amount&);
        const Worker& get_worker() const noexcept;
        Amount get_amount() const noexcept;
    private:
        const Worker* worker;
        Amount amount;
};

std::ostream& operator<<(std::ostream&, const Paycheck&);

#endif
