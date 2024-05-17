#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>
#include <string>
#include "../workers/worker.hpp"
#include "../rooms/hpp/room.hpp"
#include "../types/guest.hpp"
#include "../types/stay.hpp"

class UnsupportedWorkerTypeError : public std::invalid_argument
{
    public:
        UnsupportedWorkerTypeError(const std::string& what, const Worker&);
        const Worker& worker;
};

class DuplicateWorkerIDError : public std::invalid_argument
{
    public:
        DuplicateWorkerIDError(const std::string& what, const Worker&);
        const Worker& worker;
};

class InvalidWorkerError : public std::invalid_argument
{
    public:
        InvalidWorkerError(const std::string& what, const Worker&);
        const Worker& worker;
};

class IDNotFoundError : public std::invalid_argument
{
    public:
        IDNotFoundError(const std::string& what, const std::string& id);
        std::string id;
};

class IncorrectWorkerType : public std::invalid_argument
{
    public:
        IncorrectWorkerType(const std::string& what, const Worker&, WorkerType);
        const Worker& worker;
        WorkerType type;
};

class RoomCapacityExceededError : public std::invalid_argument
{
    public:
        RoomCapacityExceededError(const std::string& what, const Room&);
        const Room& room;
};

class GuestNotInSystemError : public std::invalid_argument
{
    public:
        GuestNotInSystemError(const std::string& what, const Guest&);
        const Guest& guest;
};

class RoomNotInSystemError : public std::invalid_argument
{
    public:
        RoomNotInSystemError(const std::string& what, const Room&);
        const Room& room;
};

class StayOverlapError : public std::invalid_argument
{
    public:
        StayOverlapError(const std::string& what, const Stay& old_stay, const Stay& new_stay);
        const Stay& old_stay;
        const Stay& new_stay;
};

class WorkerNotInSystemError : public std::invalid_argument
{
    public:
        WorkerNotInSystemError(const std::string& what, const Worker&);
        const Worker& worker;
};

class TurnBackTimeError : public std::invalid_argument
{
    public:
        TurnBackTimeError(const std::string& what, const jed_utils::datetime& time);
        jed_utils::datetime time;
};

#endif
