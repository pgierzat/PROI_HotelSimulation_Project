#include "id_generator.hpp"
#include <algorithm>


IDGenerator::IDGenerator() {};

std::string IDGenerator::generate_id() noexcept
{
    std::vector<std::string>::iterator p{};
    std::string proposition;
    do
    {
        proposition = std::to_string(++count);
        p = std::ranges::find(forbidden, proposition);
    } while (p != forbidden.end());
    return proposition;
}

void IDGenerator::forbid_id(const std::string& id) noexcept
{
    forbidden.push_back(id);
}
