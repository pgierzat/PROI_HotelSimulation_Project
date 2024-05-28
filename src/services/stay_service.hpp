#ifndef STAY_SERVICE_HPP
#define STAY_SERVICE_HPP

#include "service.hpp"
#include "../types/stay.hpp"

class StayService : public Service
{
    public:
        StayService(const std::string& id, const Stay&);
        Amount get_default_price() const noexcept override;
        const Stay& get_stay() const noexcept;
        const std::string& get_description() const noexcept override;
        ServiceStatus refresh_status(const ServiceSystem&) override;
        void add_to_systems(ServiceSystem&) override;
        static void set_s_system(StaySystem& s_system);
    private:
        static StaySystem* s_system;
        static const std::string description;
        Amount price;
        std::string stay_id;
};

#endif
