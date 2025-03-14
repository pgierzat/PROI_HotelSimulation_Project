#include "pay.hpp"

const std::map<std::string, PaycheckMethod> Pay::str_to_method_map = {
    {"Salary", PaycheckMethod::Salary},
    {"Wage", PaycheckMethod::Wage}
};

const std::map<PaycheckMethod, std::string> Pay::method_to_str_map = {
    {PaycheckMethod::Salary, "Salary"},
    {PaycheckMethod::Wage, "Wage"}
};

Pay::Pay(PaycheckMethod method, Amount amount) : method{method}
{
    if (method == PaycheckMethod::Salary)
        (this -> amount).salary = amount;
    else if (method == PaycheckMethod::Wage)
        (this -> amount).wage = amount;
    else
        throw std::invalid_argument("Tried to construct Pay with unsupported PaycheckMethod.");
}

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

Amount Pay::get_amount() const noexcept
{
    if (method == PaycheckMethod::Salary)
        return amount.salary;
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

PaycheckMethod Pay::method_from_str(const std::string& str) {
    return str_to_method_map.at(str);
}

const std::string& Pay::method_to_str(PaycheckMethod method) {
    return method_to_str_map.at(method);
}
