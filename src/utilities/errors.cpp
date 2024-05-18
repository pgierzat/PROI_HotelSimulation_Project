#include "errors.hpp"

UnsupportedWorkerTypeError::UnsupportedWorkerTypeError(const std::string& what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

DuplicateWorkerIDError::DuplicateWorkerIDError(const std::string& what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

InvalidWorkerError::InvalidWorkerError(const std::string& what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

IDNotFoundError::IDNotFoundError(const std::string& what, const std::string& id) :
    std::invalid_argument(what), id{id} {}

IncorrectWorkerType::IncorrectWorkerType(const std::string& what, const Worker& worker, WorkerType type) :
    std::invalid_argument(what), worker{worker}, type{type} {}

RoomCapacityExceededError::RoomCapacityExceededError(const std::string& what, const Room& room) : 
    std::invalid_argument(what), room{room} {}

GuestNotInSystemError::GuestNotInSystemError(const std::string& what, const Guest& guest) :
    std::invalid_argument(what), guest{guest} {}

RoomNotInSystemError::RoomNotInSystemError(const std::string& what, const Room&) :
    std::invalid_argument(what), room{room} {}

StayOverlapError::StayOverlapError(const std::string& what, const Stay& old_stay, const Stay& new_stay) :
    std::invalid_argument{what}, old_stay{old_stay}, new_stay{new_stay} {}

WorkerNotInSystemError::WorkerNotInSystemError(const std::string& what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

TurnBackTimeError::TurnBackTimeError(const std::string& what, const jed_utils::datetime& time) :
    std::invalid_argument(what), time{time} {}

TaskStatusError::TaskStatusError(const std::string& what, const Task&) :
    std::invalid_argument(what), task{task} {}

TaskAssignmentError::TaskAssignmentError(const std::string& what, const Task&, const Worker&) :
    std::invalid_argument(what), task{task}, worker{worker} {}

DuplicateClientError::DuplicateClientError(const std::string& what, const Table& table, const Guest& client) :
    std::invalid_argument(what), table{table}, client{client} {}
