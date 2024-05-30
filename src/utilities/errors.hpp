#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>
#include <string>


class Worker;
enum class WorkerType : unsigned;
class Room;
class Guest;
class Table;
class Stay;
enum class StayStatus : unsigned;
class Service;
class Task;
class TimetableEntry;
namespace jed_utils {
    class datetime;
    class timespan;
}
namespace nlohmann {
    class json;
}


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

class DuplicateTaskIDError : public std::invalid_argument
{
    public:
        DuplicateTaskIDError(const std::string& what, const Task&);
        const Task& task;
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
        RoomCapacityExceededError(const std::string& what, const Stay&);
        const Stay& stay;
};

class GuestNotInSystemError : public std::invalid_argument
{
    public:
        GuestNotInSystemError(const std::string& what, const Guest&);
        GuestNotInSystemError(const std::string& what, const std::string& guest_id);
        const Guest* guest = nullptr;
        const std::string& guest_id ="";
};

class RoomNotInSystemError : public std::invalid_argument
{
    public:
        RoomNotInSystemError(const std::string& what, const Room&);
        RoomNotInSystemError(const std::string& what, unsigned room_nr);
        const Room* room = nullptr;
        unsigned room_nr = -1;
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
        WorkerNotInSystemError(const std::string& what, const std::string& worker_id);
        const Worker* worker = nullptr;
        const std::string worker_id = "";
};

class TaskNotInSystemError : public std::invalid_argument
{
    public:
        TaskNotInSystemError(const std::string& what, const Task&);
        TaskNotInSystemError(const std::string& what, const std::string& task_id);
        const Task* task = nullptr;
        const std::string& task_id = "";
};

class TurnBackTimeError : public std::invalid_argument
{
    public:
        TurnBackTimeError(const std::string& what, const jed_utils::datetime& time);
        const jed_utils::datetime& time;
};

class TaskStatusError : public std::invalid_argument
{
    public:
        TaskStatusError(const std::string& what, const Task&);
        const Task& task;
};

class TaskAssignmentError : public std::invalid_argument
{
    public:
        TaskAssignmentError(const std::string& what, const Task&, const Worker&);
        const Task& task;
        const Worker& worker;
};

class DuplicateClientError : public std::invalid_argument
{
    public:
        DuplicateClientError(const std::string& what, const Table&, const Guest&);
        const Table& table;
        const Guest& client;
};

class TaskCapacityError : public std::invalid_argument
{
    public:
        TaskCapacityError(const std::string& what, const Task&, const Worker&);
        const Task& task;
        const Worker& worker;
};

class SystemNotBoundError : public std::invalid_argument
{
    public:
        SystemNotBoundError(const std::string& what);
};

class ServiceStatusError : public std::invalid_argument
{
    public:
        ServiceStatusError(const std::string& what, const Service&);
        const Service& service;
};

class UnknownStayStatusError : public std::invalid_argument
{
    public:
        UnknownStayStatusError(const std::string& what, StayStatus);
        StayStatus status;
};

class StayStatusError : public std::invalid_argument
{
    public:
        StayStatusError(const std::string& what, const Stay& stay);
        const Stay& stay;
};

class StayBackwardBookError : public std::invalid_argument
{
    public:
        StayBackwardBookError(const std::string& what, const Stay&, const jed_utils::datetime&);
        const Stay& stay;
};

class StayNotInSystemError : public std::invalid_argument
{
    public:
        StayNotInSystemError(const std::string& what, const Stay&);
        StayNotInSystemError(const std::string& what, const std::string& stay_id);
        const Stay* stay = nullptr;
        const std::string& stay_id = "";
};

class UninitializedServiceError : public std::invalid_argument
{
    public:
        UninitializedServiceError(const std::string& what, const Service&);
        const Service& service;
};

class EntryScheduleError : public std::invalid_argument
{
    public:
        EntryScheduleError(const std::string& what, const TimetableEntry&);
        const TimetableEntry& entry;
};

class EntryStatusError : public std::invalid_argument
{
    public:
        EntryStatusError(const std::string& what, const TimetableEntry&);
        const TimetableEntry& entry;
};

class ServiceNotInSystemError : public std::invalid_argument
{
    public:
        ServiceNotInSystemError(const std::string& what, const Service&);
        ServiceNotInSystemError(const std::string& what, const std::string service_id);
        const Service* service = nullptr;
        std::string service_id = "";
};

class JSONException : public std::runtime_error
{
public:
    JSONException(const std::string&, const nlohmann::json& j);
    const nlohmann::json& j;
};

class JSONInvalidData : public std::runtime_error
{
public:
    JSONInvalidData(const std::string&, const nlohmann::json& j);
    const nlohmann::json& j;
};

#endif
