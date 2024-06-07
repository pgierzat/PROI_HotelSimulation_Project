#ifndef GUEST_SYSTEM_HPP
#define GUEST_SYSTEM_HPP

#include "../auxiliary/other_system_publisher.hpp"
#include "../types/guest.hpp"
#include <vector>
#include <optional>
#include <memory>


class GuestSystem : public OtherSystemPublisher<Guest>
{
    public:
        GuestSystem() = default;
        GuestSystem(const GuestSystem&) = delete;
        void add_guest(const Guest&);
        void remove_guest(const Guest&) noexcept;
        std::optional<const Guest*> find_by_id(const std::string& id) const noexcept;
        const Guest& get_by_id(const std::string& id) const;
        std::vector<const Guest*> get_guests() const noexcept;
    private:
        std::vector<std::unique_ptr<Guest>> guests;
};

#endif