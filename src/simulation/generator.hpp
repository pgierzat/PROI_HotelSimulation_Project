#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "../systems/task_system.hpp"
#include "../types/datetime.h"
#include "../types/timespan.h"


class Generator
{
    public:
        Generator(const jed_utils::datetime&);
        virtual void set_time(const jed_utils::datetime&);
    protected:
        virtual ~Generator() {};
        virtual void generate() = 0;
        virtual jed_utils::timespan get_time_of_gen() const noexcept;
        virtual void set_time_next() noexcept;
        jed_utils::datetime time;
        jed_utils::datetime time_next;
};

#endif
