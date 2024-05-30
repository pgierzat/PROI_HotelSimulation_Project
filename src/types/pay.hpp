#ifndef PAY_HPP
#define PAY_HPP

#include <map>
#include "amount.hpp"

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
        Amount get_amount() const noexcept;
        PaycheckMethod get_method() const noexcept;
        void set_salary(const Amount&);
        void set_wage(const Amount&);
        bool operator==(const Pay&) const;
        static PaycheckMethod method_from_str(const std::string&);
        static const std::string& method_to_str(PaycheckMethod);
    private:
        static const std::map<std::string, PaycheckMethod> str_to_method;
        static const std::map<PaycheckMethod, std::string> method_to_str;
        PaycheckMethod method;
        PayUnion amount;
};

#endif
