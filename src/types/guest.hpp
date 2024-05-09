#ifndef GUEST_HPP
#define GUEST_HPP

#include <string>

class Guest
{
    public:
        Guest(const std::string& name);
    private:
        std::string name;
};

#endif