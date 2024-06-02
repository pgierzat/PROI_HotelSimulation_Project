#include <string>
#include <map>
#include "worker.hpp"

#ifndef WAITER_HPP
#define WAITER_HPP

class Waiter : public Worker
{
    public:
        Waiter(std::string id, std::string name, const Pay&);
        Waiter() = default;
        Amount calculate_paycheck(unsigned hours_worked) const noexcept override;
        WorkerType get_type() const noexcept override;
        unsigned get_shifts() const noexcept override;
        unsigned get_workers_per_shift() const noexcept override; 
        jed_utils::timespan get_shift_start(Shift) const override;
        jed_utils::timespan get_shift_duration() const noexcept override;
        unsigned get_orders_taken() const noexcept;

        void set_orders_taken(unsigned) noexcept;
        void reset_stats() override;

        static const Amount& get_bonus();
        static void set_workers_per_shift(unsigned);
        static const WorkerType type = WorkerType::Waiter;
    private:
        unsigned orders_taken = 0;
        static const unsigned shifts = 1;
        static unsigned workers_per_shift;
        static const Amount bonus;
        static const jed_utils::timespan shift_duration;
        static const std::map<Shift, jed_utils::timespan> shifts_to_hours;
};

#endif
