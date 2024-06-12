#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include "../types/datetime.h"
#include "../types/timespan.h"
#include "../auxiliary/time_observer.hpp"
#include "../auxiliary/time_publisher.hpp"
#include "../systems/clock.hpp"
#include <random>


class RandomGenerator : public TimeObserver
{
        using datetime = jed_utils::datetime;
        using timespan = jed_utils::timespan;
    public:
        RandomGenerator(Clock&, double prop, timespan prop_unit_delta);
        virtual ~RandomGenerator() = default;
        void notify(const datetime&) override;
    protected:
        virtual void generate() = 0;
        datetime time;
        double prop;
        std::default_random_engine engine;
        std::uniform_real_distribution<double> real_dist{0, 1};
        
};

#endif
