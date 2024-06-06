#include "task_assigner.hpp"

TaskAssigner::TaskAssigner(HotelSystem& h_system) :
    t_system{&h_system.get_t_system()},
    w_system{&h_system.get_cw_system()} {}

