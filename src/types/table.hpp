#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <string>

class Guest;
class GuestSystem;

class Table
{
    public:
        Table(const std::string& number);
        const std::string& get_number() const noexcept;
        const std::vector<const Guest*> get_clients() const;
        void assign_client(const Guest&);
        void unassign_clients() noexcept;
        bool operator==(const Table&) const;
        static void set_g_system(const GuestSystem&) noexcept;
    private:
        static const GuestSystem* g_system;

        std::string number;
        std::vector<std::string> clients;
};

#endif
