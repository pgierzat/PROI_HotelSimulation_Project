#include "random_generator.hpp"
#include <cmath>


RandomGenerator::RandomGenerator(Clock& t_publisher, double prop, timespan prop_unit_delta) :
    time{t_publisher.get_time()}, prop{prop}
{
    if (prop < 0 || prop > 1)
        throw std::invalid_argument("invalid propability.");
    if (prop_unit_delta.get_total_minutes() == 0)
        throw std::invalid_argument("prop_unit_delta must not be zero.");
    double ratio = t_publisher.get_unit_delta().get_total_minutes() / prop_unit_delta.get_total_minutes();
    prop = 1 - std::pow(1 - prop, ratio);   // adjust prop, so that propability isn't dependent on clock rate.
    t_publisher.subscribe(*this);
}

void RandomGenerator::notify(const datetime& time)
{
    this -> time = time;
    auto x = real_dist(engine);
    if (x < prop)
        generate();
}
