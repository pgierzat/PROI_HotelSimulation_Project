#include "inner_paycheck.hpp"


InnerPaycheck::InnerPaycheck(const Paycheck& paycheck) : Paycheck{paycheck} {}
OwnSystemObserver<Worker>& InnerPaycheck::get_worker_observer() noexcept { return *this; }
const OwnSystemObserver<Worker>& InnerPaycheck::get_cworker_observer() const noexcept { return *this; }
