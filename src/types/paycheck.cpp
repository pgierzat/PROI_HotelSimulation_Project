#include "paycheck.hpp"
#include "../workers/worker.hpp"

Paycheck::Paycheck(const Worker& worker, const Amount& amount) : worker{&worker}, amount{amount} {}

const Worker& Paycheck::get_worker() const noexcept { return *worker; }

Amount Paycheck::get_amount() const noexcept { return amount; }

std::ostream& operator<<(std::ostream& os, const Paycheck& paycheck)
{
    return os << paycheck.get_worker().get_id() << ' ' << paycheck.get_amount();
}
