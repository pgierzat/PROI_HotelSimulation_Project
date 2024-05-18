#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include "guest.hpp"

class Table
{
    public:
        Table(const std::string& number);
        const std::string& get_number() const noexcept;
        const std::vector<const Guest*>& get_clients() const noexcept;
        void assign_client(const Guest&);
        void unassign_clients() noexcept;
        bool operator==(const Table&);
    private:
        std::string number;
        std::vector<const Guest*> clients;
};

#endif
