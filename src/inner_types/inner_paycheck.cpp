#include "inner_paycheck.hpp"


InnePaycheck::InnePaycheck(const Paycheck& paycheck) : Paycheck{paycheck} {}
OwnSystemObserver<Worker>& InnePaycheck::get_worker_observer() noexcept { return *this; }
const OwnSystemObserver<Worker>& InnePaycheck::get_cworker_observer() const noexcept { return *this; }
