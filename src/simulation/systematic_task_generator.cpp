#include "systematic_task_generator.hpp"
#include "../utilities/errors.hpp"

SystematicTaskGenerator::SystematicTaskGenerator(const jed_utils::datetime& time, TaskSystem& t_system) :
    Generator{time}, t_system{&t_system} {}
