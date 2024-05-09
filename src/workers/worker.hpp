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
#include "/opt/timespan.h"

#ifndef WORKER_HPP
#define WORKER_HPP


class Worker
{
    protected:
        Worker(std::string name, std::string id, const Pay&);
        Worker(const Worker&);
        Worker() = default;
        Worker(Worker&&);
        Worker& operator=(const Worker&);
        Worker& operator=(Worker&&);
    public:
        virtual ~Worker() = default;

        std::string get_name() const noexcept;
        std::string get_id() const noexcept;
        PaycheckMethod get_paycheck_method() const noexcept;
        Amount get_salary() const;
        Amount get_wage() const;
        unsigned get_hours_worked() const noexcept;
        virtual WorkerType get_type() const noexcept = 0;
        virtual unsigned get_shifts() const noexcept = 0;
        virtual jed_utils::timespan get_shift_start(Shift) const = 0;
        virtual jed_utils::timespan get_shift_duration() const noexcept = 0;

        Amount calculate_base_paycheck() const noexcept;
        virtual Amount calculate_paycheck() const noexcept = 0;

        void set_name(const std::string&);
        void set_id(const std::string&);
        void set_paycheck_method(PaycheckMethod method);
        void set_salary(const Amount&);
        void set_wage(const Amount&);
        void set_hours_worked(unsigned);
        virtual void reset_stats() = 0;

        bool operator==(const Worker&) const;
    private:
        std::string name = "";
        std::string id = "";
        Pay pay = Pay{};
        unsigned hours_worked = 0;
    protected:
        std::unique_ptr<PaycheckCalculator> calculator = nullptr;
        static std::unique_ptr<PaycheckCalculator> create_calculator(Worker*, PaycheckMethod);
};

std::ostream& operator<<(std::ostream&, const Worker&);

#endif
