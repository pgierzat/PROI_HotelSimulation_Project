#include "worker_maps.hpp"


const std::map<Shift, std::string> shift_to_str_map {
    {Shift::I, "I"},
    {Shift::II, "II"},
    {Shift::III, "III"}
};

const std::map<std::string, Shift> str_to_shift_map {
    {"I", Shift::I},
    {"II", Shift::II},
    {"III", Shift::III}
};

const std::map<WorkerType, std::string> wtype_to_str_map {
    {WorkerType::Cook, "Cook"},
    {WorkerType::Maid, "Maid"},
    {WorkerType::Receptionist, "Receptionist"},
    {WorkerType::Waiter, "Waiter"}
};

const std::map<std::string, WorkerType> str_to_wtype_map {
    {"Cook", WorkerType::Cook},
    {"Maid", WorkerType::Maid},
    {"Receptionist", WorkerType::Receptionist},
    {"Waiter", WorkerType::Waiter}
};
