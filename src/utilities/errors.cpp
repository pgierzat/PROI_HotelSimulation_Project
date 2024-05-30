#include "errors.hpp"

UnsupportedWorkerTypeError::UnsupportedWorkerTypeError(const std::string& what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

DuplicateWorkerIDError::DuplicateWorkerIDError(const std::string& what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

DuplicateTaskIDError::DuplicateTaskIDError(const std::string& what, const Task& task) :
    std::invalid_argument(what), task{task} {}

InvalidWorkerError::InvalidWorkerError(const std::string& what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

IDNotFoundError::IDNotFoundError(const std::string& what, const std::string& id) :
    std::invalid_argument(what), id{id} {}

IncorrectWorkerType::IncorrectWorkerType(const std::string& what, const Worker& worker, WorkerType type) :
    std::invalid_argument(what), worker{worker}, type{type} {}

RoomCapacityExceededError::RoomCapacityExceededError(const std::string& what, const Stay& stay) : 
    std::invalid_argument(what), stay{stay} {}


GuestNotInSystemError::GuestNotInSystemError(const std::string& what, const Guest& guest) :
    std::invalid_argument(what), guest{&guest} {}

GuestNotInSystemError::GuestNotInSystemError(const std::string& what, const std::string& guest_id) :
    std::invalid_argument(what), guest_id{guest_id} {}


RoomNotInSystemError::RoomNotInSystemError(const std::string& what, const Room& room) :
    std::invalid_argument(what), room{&room} {}

RoomNotInSystemError::RoomNotInSystemError(const std::string& what, unsigned room_nr) :
    std::invalid_argument(what), room_nr{room_nr} {}


StayOverlapError::StayOverlapError(const std::string& what, const Stay& old_stay, const Stay& new_stay) :
    std::invalid_argument{what}, old_stay{old_stay}, new_stay{new_stay} {}


WorkerNotInSystemError::WorkerNotInSystemError(const std::string& what, const Worker& worker) :
    std::invalid_argument(what), worker{&worker} {}

WorkerNotInSystemError::WorkerNotInSystemError(const std::string& what, const std::string& worker_id) :
    std::invalid_argument(what), worker_id{worker_id} {}


TaskNotInSystemError::TaskNotInSystemError(const std::string& what, const Task& task) :
    std::invalid_argument(what), task{&task} {}

TaskNotInSystemError::TaskNotInSystemError(const std::string& what, const std::string& task_id) :
    std::invalid_argument(what), task_id{task_id} {}


TurnBackTimeError::TurnBackTimeError(const std::string& what, const jed_utils::datetime& time) :
    std::invalid_argument(what), time{time} {}

TaskStatusError::TaskStatusError(const std::string& what, const Task&) :
    std::invalid_argument(what), task{task} {}

TaskAssignmentError::TaskAssignmentError(const std::string& what, const Task&, const Worker&) :
    std::invalid_argument(what), task{task}, worker{worker} {}

DuplicateClientError::DuplicateClientError(const std::string& what, const Table& table, const Guest& client) :
    std::invalid_argument(what), table{table}, client{client} {}

TaskCapacityError::TaskCapacityError(const std::string& what, const Task& task, const Worker& worker) :
    std::invalid_argument(what), task{task}, worker{worker} {}

SystemNotBoundError::SystemNotBoundError(const std::string& what) :
    std::invalid_argument(what) {}

ServiceStatusError::ServiceStatusError(const std::string& what, const Service& service) :
    std::invalid_argument(what), service{service} {}

UnknownStayStatusError::UnknownStayStatusError(const std::string& what, StayStatus status) :
    std::invalid_argument(what), status{status} {}

StayStatusError::StayStatusError(const std::string& what, const Stay& stay) :
    std::invalid_argument(what), stay{stay} {}

StayBackwardBookError::StayBackwardBookError(const std::string& what, const Stay& stay,
    const jed_utils::datetime& time) : std::invalid_argument(what), stay{stay} {}


StayNotInSystemError::StayNotInSystemError(const std::string& what, const Stay& stay) :
    std::invalid_argument(what), stay{&stay} {}

StayNotInSystemError::StayNotInSystemError(const std::string& what, const std::string& stay_id) :
    std::invalid_argument(what), stay_id{stay_id} {}


UninitializedServiceError::UninitializedServiceError(const std::string& what, const Service& service) :
    std::invalid_argument(what), service{service} {}

EntryScheduleError::EntryScheduleError(const std::string& what, const TimetableEntry& entry) :
    std::invalid_argument(what), entry{entry} {}

EntryStatusError::EntryStatusError(const std::string& what, const TimetableEntry& entry) :
    std::invalid_argument(what), entry{entry} {}


ServiceNotInSystemError::ServiceNotInSystemError(const std::string& what, const Service& service) :
    std::invalid_argument(what), service{&service} {}

ServiceNotInSystemError::ServiceNotInSystemError(const std::string& what, const std::string service_id) :
    std::invalid_argument(what), service_id{service_id} {}

JSONException::JSONException(const std::string& what, const nlohmann::json& j) :
    std::runtime_error(what), j{j} {}

JSONInvalidData::JSONInvalidData(const std::string& what, const nlohmann::json& j) :
    std::runtime_error(what), j{j} {}

FileError::FileError(const std::string& what, const std::string& filename) :
    std::runtime_error(what), filename{filename} {}
