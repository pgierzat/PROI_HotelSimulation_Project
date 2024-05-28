#ifndef WORKER_ENUMS_HPP
#define WORKER_ENUMS_HPP

#include <iostream>
#include <map>


enum class Shift : unsigned char {
    I = 1,
    II,
    III
};

std::ostream& operator<<(std::ostream&, Shift);

std::istream& operator>>(std::istream&, Shift&);

extern const std::map<Shift, std::string> shift_to_str;

extern const std::map<std::string, Shift> str_to_shift;

enum class WorkerType : unsigned {
    Cook,
    Maid,
    Receptionist,
    Waiter
};

std::ostream& operator<<(std::ostream&, WorkerType);

std::istream& operator>>(std::istream&, WorkerType&);

extern const std::map<WorkerType, std::string> wtype_to_str;

extern const std::map<std::string, WorkerType> str_to_wtype;

#endif
