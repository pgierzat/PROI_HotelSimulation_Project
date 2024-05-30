#include <string>
#include <map>
#include "worker.hpp"

#ifndef COOK_HPP
#define COOK_HPP

class Cook : public Worker
{
    public:
        Cook(std::string id, std::string name, const Pay&);
        Cook() = default;
        Amount calculate_paycheck(unsigned hours_worked) const noexcept override;
        WorkerType get_type() const noexcept override;
        unsigned get_shifts() const noexcept override;
        jed_utils::timespan get_shift_start(Shift) const override;
        jed_utils::timespan get_shift_duration() const noexcept override;
        unsigned get_dishes_prepared() const noexcept;

        void set_dishes_prepared(unsigned) noexcept;
        void reset_stats() override;

        static const WorkerType type = WorkerType::Cook;
        static const Amount bonus;
    private:
        unsigned dishes_prepared = 0;
        static unsigned shifts;
        static const jed_utils::timespan shift_duration;
        static const std::map<Shift, jed_utils::timespan> shifts_to_hours;
};

#endif
