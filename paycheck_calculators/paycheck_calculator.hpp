#include "../amount.hpp"
#include "../paycheck.hpp"

class Worker;

#ifndef PAYCHECK_CALCULATOR
#define PAYCHECK_CALCULATOR

class PaycheckCalculator
{
    protected:
        PaycheckCalculator(const Worker&);
        const Worker* worker;
    public:
        virtual Amount calculate_paycheck() const noexcept = 0;
};

#endif
