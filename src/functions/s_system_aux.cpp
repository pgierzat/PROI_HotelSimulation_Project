#include "s_system_aux.hpp"
#include "../utilities/errors.hpp"

RegressionStatus check_regression(const Stay& stay, StayStatus new_status)
{
    auto prev_status = stay.get_status();
    if (new_status < prev_status)
        throw StayStatusError("Tried to reverse stay's progress.", stay);
    if (new_status == prev_status)
        return RegressionStatus::equal;
    return RegressionStatus::progression;
}
