#include "table.hpp"
#include "../utilities/errors.hpp"
#include <algorithm>

Table::Table(const std::string& number) : number{number} {}

const std::string& Table::get_number() const noexcept { return number; }

const std::vector<const Guest*>& Table::get_clients() const noexcept { return clients; }

void Table::assign_client(const Guest& client)
{
    auto p = std::ranges::find_if(clients, [&](const Guest* otr_client){ return *otr_client == client; });
    if (p != clients.end() )
        throw DuplicateClientError("Tried to assign the same client twice to a table.", *this, client);
    clients.push_back(&client);
}

void Table::unassign_clients() noexcept { clients.clear(); }

bool Table::operator==(const Table& other) { return number == other.number; }
