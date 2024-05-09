#include "errors.hpp"

UnsupportedWorkerTypeError::UnsupportedWorkerTypeError(std::string what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

DuplicateWorkerIDError::DuplicateWorkerIDError(std::string what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

InvalidWorkerError::InvalidWorkerError(std::string what, const Worker& worker) :
    std::invalid_argument(what), worker{worker} {}

IDNotFoundError::IDNotFoundError(std::string what, const std::string& id) :
    std::invalid_argument(what), id{id} {}

IncorrectWorkerType::IncorrectWorkerType(std::string what, const Worker& worker, WorkerType type) :
    std::invalid_argument(what), worker{worker}, type{type} {}
