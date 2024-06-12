#ifndef STAY_SERVICE_HPP
#define STAY_SERVICE_HPP

#include "service.hpp"
#include "../types/stay.hpp"

class StayService : public Service, protected OwnSystemObserver<Stay>
{
        using OSO = OwnSystemObserver<Stay>;
    public:
        StayService(const std::string& id, const Stay&);
        Amount get_default_price() const noexcept override;
        const Stay& get_stay() const noexcept;
        const std::string& get_description() const noexcept override;
        void add_to_systems(ServiceSystem&) override;
    private:
        static const std::string description;
        Amount price;
        const Stay* stay;
};

#endif
