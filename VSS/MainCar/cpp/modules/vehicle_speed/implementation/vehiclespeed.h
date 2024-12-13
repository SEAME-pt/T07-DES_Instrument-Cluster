
#pragma once
#include "vehicle_speed/generated/api/vehicle_speed.h"
#include "vehicle_speed/generated/api/common.h"
#include "vehicle_speed/generated/core/vehiclespeed.data.h"
#include <memory>

namespace Cpp {
namespace VehicleSpeed {

/**
* The VehicleSpeed implementation.
*/
class CPP_VEHICLE_SPEED_EXPORT VehicleSpeed : public IVehicleSpeed
{
public:
    explicit VehicleSpeed();
    ~VehicleSpeed();
public:
    /**
    * Speed Vehicle speed in kilometers per hour
    */
    void setSpeed(float Speed) override;
    float getSpeed() const override;
    
    /**
    * Access to a publisher, use it to subscribe for VehicleSpeed changes and signal emission.
    * @return The publisher for VehicleSpeed.
    */
    IVehicleSpeedPublisher& _getPublisher() const override;
private:
    /** The publisher for the VehicleSpeed. */
    std::unique_ptr<IVehicleSpeedPublisher> m_publisher;
    /** The helper structure to store all the properties for VehicleSpeed. */
    VehicleSpeedData m_data;
};
} // namespace VehicleSpeed
} // namespace Cpp
