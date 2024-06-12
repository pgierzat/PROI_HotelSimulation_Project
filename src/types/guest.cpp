#include "guest.hpp"
#include <stdexcept>
#include "../functions/check_empty.hpp"


Guest::Guest(const std::string& id, const std::string& name) : id{id}, name{name} {}

const std::string& Guest::get_name() const noexcept { return name; }

const std::string& Guest::get_id() const noexcept { return id; }

void Guest::set_name(const std::string& name) { this -> name = name; }

void Guest::set_id(const std::string& id) { this -> id = id; }
