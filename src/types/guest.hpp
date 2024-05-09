#ifndef GUEST_HPP
#define GUEST_HPP

#include <string>

class Guest
{
    public:
        Guest(const std::string& name);
        std::string get_name() const noexcept;
        void set_name(const std::string&);
    private:
        static void validate_name(const std::string& name);
        std::string name;
};

#endif