#include "paycheck.hpp"
#include "../workers/worker.hpp"
#include "../systems/worker_system.hpp"

Paycheck::Paycheck(const Worker& worker, const Amount& amount) :
    w_observer{worker}, amount{amount} {}

const Worker& Paycheck::get_worker() const { return w_observer.get_observed(); }

const std::string& Paycheck::get_worker_id() const { return w_observer.get_observed_id(); }

Amount Paycheck::get_amount() const noexcept { return amount; }

bool Paycheck::operator==(const Paycheck& other) const
{
    return get_worker() == other.get_worker() &&
        amount == other.amount;
}

OwnSystemObserver<Worker>& Paycheck::get_w_observer() noexcept { return w_observer; }

std::ostream& operator<<(std::ostream& os, const Paycheck& paycheck)
{
    return os << paycheck.get_worker().get_id() << ' ' << paycheck.get_amount();
}
