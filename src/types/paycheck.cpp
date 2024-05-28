#include "paycheck.hpp"
#include "../workers/worker.hpp"
#include "../systems/worker_system.hpp"

const WorkerSystem* Paycheck::w_system = nullptr;

Paycheck::Paycheck(const Worker& worker, const Amount& amount) :
    worker_id{worker.get_id()}, amount{amount} {}

const Worker& Paycheck::get_worker() const
{
    return w_system -> get_by_id(worker_id);
}

Amount Paycheck::get_amount() const noexcept { return amount; }

bool Paycheck::operator==(const Paycheck& other) const
{
    return worker_id == other.worker_id &&
        amount == other.amount;
}

void Paycheck::set_w_system(const WorkerSystem& w_system)
{
    Paycheck::w_system = &w_system;
}

std::ostream& operator<<(std::ostream& os, const Paycheck& paycheck)
{
    return os << paycheck.get_worker().get_id() << ' ' << paycheck.get_amount();
}
