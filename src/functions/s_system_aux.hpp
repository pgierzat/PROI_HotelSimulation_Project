#include "../inner_types/inner_stay.hpp"
#include "../types/time_interval.hpp"

enum class RegressionStatus {
    regression,
    equal,
    progression
};

RegressionStatus check_regression(const Stay&, StayStatus new_status);

class StaySameRoomID
{
    public:
        StaySameRoomID(const Room&) noexcept;
        StaySameRoomID(const std::string& room_id) noexcept;
        bool operator()(const InnerStay&) const noexcept;
        bool operator()(const std::unique_ptr<InnerStay>&) const noexcept;
    private:
        const std::string& room_id;
};

class StayHasGuestID
{
    public:
        StayHasGuestID(const Guest&) noexcept;
        StayHasGuestID(const std::string& guest_id) noexcept;
        bool operator()(const InnerStay&) const noexcept;
        bool operator()(const std::unique_ptr<InnerStay>&) const noexcept;
    private:
        const std::string& guest_id;
};
