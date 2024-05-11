#include "amount.hpp"

#ifndef PAY_HPP
#define PAY_HPP

enum class PaycheckMethod : unsigned char {
    Salary,
    Wage
};

class Pay
{
        union PayUnion
        {
            PayUnion() { salary = Amount{}; }
            Amount salary;
            Amount wage;
        };
    public:
        Pay(PaycheckMethod method, Amount amount);
        Pay() = default;
        Amount get_salary() const;
        Amount get_wage() const;
        PaycheckMethod get_method() const noexcept;
        void set_salary(const Amount&);
        void set_wage(const Amount&);
        bool operator==(const Pay&) const;
    private:
        PaycheckMethod method;
        PayUnion amount;
};

#endif
