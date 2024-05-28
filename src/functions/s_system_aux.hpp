#include "../types/stay.hpp"
#include "../types/time_interval.hpp"

enum class RegressionStatus {
    regression,
    equal,
    progression
};

RegressionStatus check_regression(const Stay&, StayStatus new_status);
