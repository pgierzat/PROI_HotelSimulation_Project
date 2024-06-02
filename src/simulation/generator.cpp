#include "generator.hpp"
#include "../utilities/errors.hpp"

Generator::Generator(const jed_utils::datetime& time) : time{time}, time_next{time} {}

void Generator::set_time(const jed_utils::datetime& time)
{
    auto prev_time = this -> time;
    if (time < prev_time)
        throw TurnBackTimeError("Tried to turn Generator's time back.", time);
    if (time_next <= time)
    {
        this -> generate();
        this -> set_time_next();
    }
    this -> time = time;
}

jed_utils::timespan Generator::get_time_of_gen() const noexcept{ 
    return jed_utils::timespan{0};
}

void Generator::set_time_next() noexcept
{
    time_next.add_days(1);
}
