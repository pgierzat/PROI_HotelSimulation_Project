#include "amount.hpp"

#ifndef PAY_HPP
#define PAY_HPP

enum class PaycheckMethod : unsigned char {
    NoneType,
    Salary,
    Wage
};

class Pay
{
        union PayType
        {
            PayType() { salary = Amount{}; }
            Amount salary;
            Amount wage;
        };
    public:
        Pay(PaycheckMethod method, Amount amount);
        Pay(PaycheckMethod method);
        Pay() = default;
        Amount get_salary() const;
        Amount get_wage() const;
        PaycheckMethod get_method() const noexcept;
        void set_salary(const Amount&);
        void set_wage(const Amount&);
    private:
        PaycheckMethod method = PaycheckMethod::NoneType;
        PayType amount;
};

#endif
