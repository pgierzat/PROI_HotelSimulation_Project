#include "guest.hpp"
#include <stdexcept>


Guest::Guest(const std::string& name) : name{name}
{
    validate_name(name);
}

std::string Guest::get_name() const noexcept { return name; }

void Guest::set_name(const std::string& name)
{
    validate_name(name);
    this -> name = name;
}

void Guest::validate_name(const std::string& name)
{
    if (name.empty())
        throw std::invalid_argument("Guest's name must not be empty");
}
