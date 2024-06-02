#include <string>
#include <map>
#include "worker.hpp"

#ifndef MAID_HPP
#define MAID_HPP

class Maid : public Worker
{
    public:
        Maid(std::string id, std::string name, const Pay&);
        Maid() = default;
        Amount calculate_paycheck(unsigned hours_worked) const noexcept override;
        WorkerType get_type() const noexcept override;
        unsigned get_shifts() const noexcept override;
        unsigned get_workers_per_shift() const noexcept override;
        jed_utils::timespan get_shift_start(Shift) const override;
        jed_utils::timespan get_shift_duration() const noexcept override;
        unsigned get_rooms_serviced() const noexcept;

        void set_rooms_serviced(unsigned) noexcept;
        void reset_stats() override;

        static const Amount& get_bonus();
        static void set_workers_per_shift(unsigned);
        static const WorkerType type = WorkerType::Maid;
    private:
        unsigned rooms_serviced = 0;
        static const unsigned shifts = 2;
        static unsigned workers_per_shift;
        static const Amount bonus;
        static const jed_utils::timespan shift_duration;
        static const std::map<Shift, jed_utils::timespan> shifts_to_hours;
};

#endif
