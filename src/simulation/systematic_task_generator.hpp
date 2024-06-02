#ifndef SYSTEMATIC_TASK_GENERATOR_HPP
#define SYSTEMATIC_TASK_GENERATOR_HPP

#include "generator.hpp"
#include "../systems/task_system.hpp"
#include "../types/datetime.h"
#include "../types/timespan.h"


class SystematicTaskGenerator : public Generator
{
    public:
        SystematicTaskGenerator(const jed_utils::datetime&, TaskSystem&);
    protected:
        TaskSystem* t_system;
};

#endif
