#include "inner_paycheck.hpp"


InnerPaycheck::InnerPaycheck(const Paycheck& paycheck) : Paycheck{paycheck} {}

InnerPaycheck::InnerPaycheck(const Worker& worker, const Amount& amount) : Paycheck{worker, amount} {}

OwnSystemObserver<Worker>& InnerPaycheck::get_worker_observer() noexcept { return *this; }
const OwnSystemObserver<Worker>& InnerPaycheck::get_cworker_observer() const noexcept { return *this; }
