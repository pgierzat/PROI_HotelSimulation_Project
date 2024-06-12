#ifndef ID_GENERATOR_HPP
#define ID_GENERATOR_HPP

#include <string>
#include <vector>

class IDGenerator
{
    public:
        IDGenerator();
        std::string generate_id() noexcept;
        void forbid_id(const std::string& id) noexcept;
        void unfordid(const std::string& id) noexcept;
    private:
        unsigned count = 0;
        std::vector<std::string> forbidden;
};

#endif
