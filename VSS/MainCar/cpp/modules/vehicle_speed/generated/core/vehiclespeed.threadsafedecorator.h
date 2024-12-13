
#pragma once
#include "vehicle_speed/generated/api/vehicle_speed.h"
#include "vehicle_speed/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Cpp {
namespace VehicleSpeed {

/** 
* @brief The VehicleSpeedThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the VehicleSpeed interface.
* @see VehicleSpeed
*
\code{.cpp}
using namespace Cpp::VehicleSpeed;

std::unique_ptr<IVehicleSpeed> testVehicleSpeed = std::make_unique<VehicleSpeedThreadSafeDecorator>(std::make_shared<VehicleSpeed>());

// Thread safe access
auto speed = testVehicleSpeed->getSpeed();
testVehicleSpeed->setSpeed(0.0f);
\endcode
*/
class CPP_VEHICLE_SPEED_EXPORT VehicleSpeedThreadSafeDecorator : public IVehicleSpeed
{
public:
    /** 
    * ctor
    * @param impl The VehicleSpeed object to make thread safe.
    */
    explicit VehicleSpeedThreadSafeDecorator(std::shared_ptr<IVehicleSpeed> impl);

    /** Guards and forwards call to VehicleSpeed implementation. */
    void setSpeed(float Speed) override;
    /** Guards and forwards call to VehicleSpeed implementation. */
    float getSpeed() const override;

    /**
    * Access to a publisher, use it to subscribe for VehicleSpeed changes and signal emission.
    * This call is thread safe.
    * @return The publisher for VehicleSpeed.
    */
    IVehicleSpeedPublisher& _getPublisher() const override;
private:
    /** The VehicleSpeed object which is guarded */
    std::shared_ptr<IVehicleSpeed> m_impl;
    // Mutex for speed property
    mutable std::shared_timed_mutex m_speedMutex;
};
} // namespace VehicleSpeed
} // namespace Cpp
