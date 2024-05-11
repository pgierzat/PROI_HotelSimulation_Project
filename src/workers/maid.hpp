#include <string>
#include <map>
#include "worker.hpp"

#ifndef MAID_HPP
#define MAID_HPP

class Maid : public Worker
{
    public:
        Maid(std::string name, std::string id, const Pay&);
        Maid() = default;
        Amount calculate_paycheck() const noexcept override;
        WorkerType get_type() const noexcept override;
        unsigned get_shifts() const noexcept override;
        jed_utils::timespan get_shift_start(Shift) const override;
        jed_utils::timespan get_shift_duration() const noexcept override;
        unsigned get_rooms_serviced() const noexcept;

        void set_rooms_serviced(unsigned) noexcept;
        void reset_stats() override;

        static const WorkerType type = WorkerType::Maid;
        static const Amount bonus;
    private:
        unsigned rooms_serviced = 0;
        static const unsigned shifts;
        static const jed_utils::timespan shift_duration;
        static const std::map<Shift, jed_utils::timespan> shifts_to_hours;
};

#endif
