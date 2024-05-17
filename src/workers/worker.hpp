#include <string>
#include <map>
#include <memory>
#include "worker_enums.hpp"
#include "../types/amount.hpp"
#include "../types/pay.hpp"
#include "../paycheck_calculators/paycheck_calculator.hpp"
#include "../paycheck_calculators/salary_calculator.hpp"
#include "../paycheck_calculators/wage_calculator.hpp"
#include "../paycheck_calculators/paycheck_calculator.hpp"
#include "../types/timespan.h"

#ifndef WORKER_HPP
#define WORKER_HPP


class Worker
{
    protected:
        Worker(std::string name, std::string id, const Pay&);
        Worker() = default;
        Worker(const Worker&);
        Worker(Worker&&);
        Worker& operator=(const Worker&);
        Worker& operator=(Worker&&);
    public:
        virtual ~Worker() = default;
        std::string get_name() const noexcept;
        std::string get_id() const noexcept;
        Pay get_pay() const noexcept;
        virtual WorkerType get_type() const noexcept = 0;
        virtual unsigned get_shifts() const noexcept = 0;
        virtual jed_utils::timespan get_shift_start(Shift) const = 0;
        virtual jed_utils::timespan get_shift_duration() const noexcept = 0;
        Amount calculate_base_paycheck(unsigned hours_worked) const noexcept;
        virtual Amount calculate_paycheck(unsigned hours_worked) const noexcept = 0;

        void set_name(const std::string&);
        void set_id(const std::string&);
        void set_pay(const Pay&);
        virtual void reset_stats() = 0;

        bool operator==(const Worker&) const;
    private:
        std::string name;
        std::string id;
        Pay pay;
    protected:
        std::unique_ptr<PaycheckCalculator> calculator = nullptr;
        static std::unique_ptr<PaycheckCalculator> create_calculator(Worker*, PaycheckMethod);
};

std::ostream& operator<<(std::ostream&, const Worker&);

#endif
