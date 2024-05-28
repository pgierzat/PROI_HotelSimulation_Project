#include "table.hpp"
#include "guest.hpp"
#include "../utilities/errors.hpp"
#include "../systems/guest_system.hpp"
#include <algorithm>

const GuestSystem* Table::g_system = nullptr;

Table::Table(const std::string& number) : number{number} {}

const std::string& Table::get_number() const noexcept { return number; }

const std::vector<const Guest*> Table::get_clients() const
{
    std::vector<const Guest*> vec;
    for (const std::string& id : clients)
        vec.push_back(&g_system -> get_by_id(id));
    return vec;
}

void Table::assign_client(const Guest& client)
{
    const auto& id = client.get_id(); 
    auto p = std::ranges::find_if(clients, [&](const auto& otr_id){ return otr_id == id; });
    if (p != clients.end() )
        throw DuplicateClientError("Tried to assign the same client twice to a table.", *this, client);
    clients.push_back(id);
}

void Table::unassign_clients() noexcept { clients.clear(); }

bool Table::operator==(const Table& other) const
{
    return number == other.number &&
        clients == other.clients;
}

void Table::set_g_system(const GuestSystem& g_system) noexcept { Table::g_system = &g_system; }
