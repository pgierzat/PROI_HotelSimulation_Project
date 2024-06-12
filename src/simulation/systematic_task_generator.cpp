#include "systematic_task_generator.hpp"
#include "../utilities/errors.hpp"

SystematicTaskGenerator::SystematicTaskGenerator(TimePublisher& t_publisher, const jed_utils::datetime& time, TaskSystem& t_system) :
    Generator{t_publisher, time}, t_system{&t_system} {}
