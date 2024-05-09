#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>
#include <string>
#include "../workers/worker.hpp"

class UnsupportedWorkerTypeError : public std::invalid_argument
{
    public:
        UnsupportedWorkerTypeError(std::string what, const Worker&);
        const Worker& worker;
};

class DuplicateWorkerIDError : public std::invalid_argument
{
    public:
        DuplicateWorkerIDError(std::string what, const Worker&);
        const Worker& worker;
};

class InvalidWorkerError : public std::invalid_argument
{
    public:
        InvalidWorkerError(std::string what, const Worker&);
        const Worker& worker;
};

class IDNotFoundError : public std::invalid_argument
{
    public:
        IDNotFoundError(std::string what, const std::string& id);
        std::string id;
};

class IncorrectWorkerType : public std::invalid_argument
{
    public:
        IncorrectWorkerType(std::string what, const Worker&, WorkerType);
        const Worker& worker;
        WorkerType type;
};

#endif
