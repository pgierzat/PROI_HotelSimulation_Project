#include "daily_generator.hpp"
#include "../utilities/errors.hpp"

DailyGenerator::DailyGenerator(TimePublisher& t_publisher, const timespan& time_of_gen) :
    time{t_publisher.get_time()}, time_next{time}, time_of_gen{time_of_gen}
{
    t_publisher.subscribe(*this);
    initiate_time_next();
}

void DailyGenerator::notify(const datetime& time)
{
    auto prev_time = this -> time;
    if (time < prev_time)
        throw TurnBackTimeError("Tried to turn DailyGenerator's time back.", time);
    if (time_next <= time)
    {
        this -> generate();
        this -> set_time_next();
    }
    this -> time = time;
}

void DailyGenerator::set_time_next() noexcept { time_next.add_days(1); }   

void DailyGenerator::initiate_time_next() noexcept
{
    time_next.trunkate();
    time_next += time_of_gen;
    if (time >= time_next)
        time_next.add_days(1);
}
