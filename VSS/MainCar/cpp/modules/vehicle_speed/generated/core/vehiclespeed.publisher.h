#pragma once

#include "vehicle_speed/generated/api/datastructs.api.h"
#include "vehicle_speed/generated/api/vehiclespeed.api.h"
#include "vehicle_speed/generated/api/common.h"

#include <atomic>
#include <vector>
#include <map>
#include <functional>
#include <shared_mutex>

namespace Cpp {
namespace VehicleSpeed {

/**
 * The implementation of a VehicleSpeedPublisher.
 * Use this class to store clients of the VehicleSpeed and inform them about the change
 * on call of the appropriate publish function.
 *
 * @warning This class is thread safe, but the subscribed classes or functions are not protected.
 */
class CPP_VEHICLE_SPEED_EXPORT VehicleSpeedPublisher : public IVehicleSpeedPublisher
{
public:
    /**
    * Implementation of IVehicleSpeedPublisher::subscribeToAllChanges
    */
    void subscribeToAllChanges(IVehicleSpeedSubscriber& subscriber) override;
    /**
    * Implementation of IVehicleSpeedPublisher::unsubscribeFromAllChanges
    */
    void unsubscribeFromAllChanges(IVehicleSpeedSubscriber& subscriber) override;

    /**
    * Implementation of IVehicleSpeedPublisher::subscribeToSpeedChanged
    */
    long subscribeToSpeedChanged(VehicleSpeedSpeedPropertyCb callback) override;
    /**
    * Implementation of IVehicleSpeedPublisher::subscribeToSpeedChanged
    */
    void unsubscribeFromSpeedChanged(long handleId) override;

    /**
    * Implementation of IVehicleSpeedPublisher::publishSpeedChanged
    */
    void publishSpeedChanged(float Speed) const override;
private:
    // Subscribers informed about any property change or signal emitted in VehicleSpeed
    std::vector<std::reference_wrapper<IVehicleSpeedSubscriber>> m_allChangesSubscribers;
    // Mutex for m_allChangesSubscribers
    mutable std::shared_timed_mutex m_allChangesSubscribersMutex;
    // Next free unique identifier to subscribe for the Speed change.
    std::atomic<long> m_speedChangedCallbackNextId {0};
    // Subscribed callbacks for the Speed change.
    std::map<long, VehicleSpeedSpeedPropertyCb> m_speedCallbacks;
    // Mutex for m_speedCallbacks
    mutable std::shared_timed_mutex m_speedCallbacksMutex;
};

} // namespace VehicleSpeed
} // namespace Cpp
