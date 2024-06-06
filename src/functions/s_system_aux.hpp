#include "../types/stay.hpp"
#include "../types/time_interval.hpp"

enum class RegressionStatus {
    regression,
    equal,
    progression
};

RegressionStatus check_regression(const Stay&, StayStatus new_status);

class StaySameRoom
{
    public:
        StaySameRoom(const Room&) noexcept;
        StaySameRoom(const std::string& room_id) noexcept;
        bool operator()(const Stay&) const noexcept;
        bool operator()(const std::unique_ptr<Stay>&) const noexcept;
    private:
        const std::string& room_id;
};

class StayHasGuest
{
    public:
        StayHasGuest(const Guest&) noexcept;
        StayHasGuest(const std::string& guest_id) noexcept;
        bool operator()(const Stay&) const noexcept;
        bool operator()(const std::unique_ptr<Stay>&) const noexcept;
    private:
        const std::string& guest_id;
};
