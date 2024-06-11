#ifndef PAYCHECK_CALCULATOR
#define PAYCHECK_CALCULATOR

class Amount;
class Worker;

class PaycheckCalculator
{
    protected:
        PaycheckCalculator(const Worker&);
        const Worker* worker;
    public:
        ~PaycheckCalculator() = default;
        virtual Amount calculate_paycheck(unsigned hours_worked) const noexcept = 0;
};

#endif
