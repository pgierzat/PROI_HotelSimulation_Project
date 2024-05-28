#include "guest.hpp"
#include <stdexcept>
#include "../functions/check_empty.hpp"


Guest::Guest(const std::string& id, const std::string& name) : id{id}, name{name}
{
    check_empty(id, "Guest's id cannot be empty.");
    check_empty(name, "Guest's name cannot be empty.");
}

const std::string& Guest::get_name() const noexcept { return name; }

const std::string& Guest::get_id() const noexcept { return id; }

void Guest::set_name(const std::string& name)
{
    check_empty(name, "Guest's name cannot be empty.");
    this -> name = name;
}

void Guest::set_id(const std::string& id) {
    check_empty(id, "Guest's id cannot be empty.");
    this -> id = id;
}
