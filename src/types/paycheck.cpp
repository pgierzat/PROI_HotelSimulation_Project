#include "paycheck.hpp"
#include "../workers/worker.hpp"
#include "../systems/worker_system.hpp"

Paycheck::Paycheck(const Worker& worker, const Amount& amount) :
    OwnSystemObserver<Worker>{worker}, amount{amount} {}

const Worker& Paycheck::get_worker() const { return WorkerObs::get(); }

Amount Paycheck::get_amount() const noexcept { return amount; }

bool Paycheck::operator==(const Paycheck& other) const
{
    return get_worker() == other.get_worker() &&
        amount == other.amount;
}

std::ostream& operator<<(std::ostream& os, const Paycheck& paycheck)
{
    return os << paycheck.get_worker().get_id() << ' ' << paycheck.get_amount();
}
