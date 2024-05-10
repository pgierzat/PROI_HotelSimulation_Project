#include "pay.hpp"

Pay::Pay(PaycheckMethod method, Amount amount) : method{method}
{
    if (method == PaycheckMethod::Salary)
        (this -> amount).salary = amount;
    else
        (this -> amount).wage = amount;
}

Pay::Pay(PaycheckMethod method) : Pay{method, Amount{}} {}

Amount Pay::get_salary() const
{
    if (method != PaycheckMethod::Salary)
        throw std::invalid_argument("That worker doesn't have a salary.");
    return amount.salary;
}

Amount Pay::get_wage() const
{
    if (method != PaycheckMethod::Wage)
        throw std::invalid_argument("That worker doesn't have a wage.");
    return amount.wage;
}

PaycheckMethod Pay::get_method() const noexcept { return method; }

void Pay::set_salary(const Amount& amount)
{
    if (method != PaycheckMethod::Salary)
        throw std::invalid_argument("That worker doesn't have a salary.");
    (this -> amount).salary = amount;
}
void Pay::set_wage(const Amount& amount)
{
    if (method != PaycheckMethod::Wage)
        throw std::invalid_argument("That worker doesn't have a wage.");
    (this -> amount).wage = amount;
}

bool Pay::operator==(const Pay& other) const
{
    if (method != other. method)
        return false;
    if (method == PaycheckMethod::Salary)
        return amount.salary == other.amount.salary;
    return amount.wage == other.amount.wage;
}