#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <concepts>
#include "../workers/cook.hpp"
#include "../workers/maid.hpp"
#include "../workers/receptionist.hpp"
#include "../workers/waiter.hpp"

template<typename T>
concept SupportedWorker =
    std::same_as<T, Cook> ||
    std::same_as<T, Maid> ||
    std::same_as<T, Receptionist> ||
    std::same_as<T, Waiter>;

#endif
