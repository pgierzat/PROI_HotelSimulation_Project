#ifndef WORKER_ENUMS_HPP
#define WORKER_ENUMS_HPP


enum class Shift : unsigned char {
    I = 1,
    II,
    III
};

enum class WorkerType : unsigned {
    Cook,
    Maid,
    Receptionist,
    Waiter
};

#endif
