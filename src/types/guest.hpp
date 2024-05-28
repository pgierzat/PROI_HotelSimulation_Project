#ifndef GUEST_HPP
#define GUEST_HPP

#include <string>

class Guest
{
    public:
        Guest(const std::string& id, const std::string& name);
        const std::string& get_name() const noexcept;
        const std::string& get_id() const noexcept;
        void set_name(const std::string&);
        void set_id(const std::string&);
        bool operator==(const Guest&) const = default;
    private:
        std::string id;
        std::string name;
};

#endif
