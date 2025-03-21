#include <string>
#include <map>
#include "worker.hpp"

#ifndef RECEPTIONIST_HPP
#define RECEPTIONIST_HPP

class Receptionist : public Worker
{
    public:
        Receptionist(std::string id, std::string name, const Pay&);
        Receptionist() = default;
        Amount calculate_paycheck(unsigned hours_worked) const noexcept override;
        WorkerType get_type() const noexcept override;
        unsigned get_shifts() const noexcept override;
        unsigned get_workers_per_shift() const noexcept override;
        jed_utils::timespan get_shift_start(Shift) const override;
        jed_utils::timespan get_shift_duration() const noexcept override;
        unsigned get_complaints() const noexcept;

        void set_complaints(unsigned) noexcept;
        void reset_stats() override;

        static const Amount& get_penalty();
        static void set_workers_per_shift(unsigned);
        static const WorkerType type = WorkerType::Receptionist;
    private:
        unsigned complaints = 0;
        static const unsigned shifts = 3;
        static unsigned workers_per_shift;
        static const Amount penalty;
        static const jed_utils::timespan shift_duration;
        static const std::map<Shift, jed_utils::timespan> shifts_to_hours;
};

#endif