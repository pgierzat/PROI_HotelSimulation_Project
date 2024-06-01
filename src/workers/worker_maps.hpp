#ifndef WORKER_MAPS_HPP
#define WORKER_MAPS_HPP

#include <map>
#include <string>
#include "worker_enums.hpp"


extern const std::map<Shift, std::string> shift_to_str_map;
extern const std::map<std::string, Shift> str_to_shift_map;
extern const std::map<WorkerType, std::string> wtype_to_str_map;
extern const std::map<std::string, WorkerType> str_to_wtype_map;

#endif
