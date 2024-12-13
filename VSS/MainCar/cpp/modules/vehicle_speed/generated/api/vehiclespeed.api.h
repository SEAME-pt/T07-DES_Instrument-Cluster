#pragma once

#include <future>
#include "vehicle_speed/generated/api/common.h"
#include "vehicle_speed/generated/api/datastructs.api.h"

namespace Cpp {
namespace VehicleSpeed {

class IVehicleSpeedSubscriber;
class IVehicleSpeedPublisher;

/**
*
* IVehicleSpeed provides an interface for
 *  - methods defined for your VehicleSpeed 
 *  - property setters and getters for defined properties
 * The IVehicleSpeed also provides an interface to access a publisher IVehicleSpeedPublisher, a class used by IVehicleSpeedSubscriber clients.
 * The implementation should notify the publisher IVehicleSpeedPublisher about emitted signals or state changed. 
 * The publisher responsibility is to keep its clients informed about requested changes.
 * See also IVehicleSpeedSubscriber, IVehicleSpeedPublisher
 * and the example implementation VehicleSpeed  or the
 */
class CPP_VEHICLE_SPEED_EXPORT IVehicleSpeed
{
public:
    virtual ~IVehicleSpeed() = default;

    /**
    * Sets the value of the Speed property.
    * @param Speed Vehicle speed in kilometers per hour
    */
    virtual void setSpeed(float Speed) = 0;
    /**
    * Gets the value of the Speed property.
    * @return Vehicle speed in kilometers per hour
    */
    virtual float getSpeed() const = 0;

    /**
    * Access to a publisher, use it to subscribe for VehicleSpeed changes and signal emission.
    * This function name doesn't follow the convention, because it is added to user defined interface,
    * to avoid potentially name clashes, it has the trailing underscore in the name.
    * @return The publisher for VehicleSpeed.
    */
    virtual IVehicleSpeedPublisher& _getPublisher() const = 0;
};


/**
 * The IVehicleSpeedSubscriber contains functions to allow informing about signals or property changes of the IVehicleSpeed implementation.
 * The implementation for IVehicleSpeed should provide mechanism for subscription of the IVehicleSpeedSubscriber clients.
 * See IVehicleSpeedPublisher, which provides facilitation for this purpose.
 * The implementation for IVehicleSpeed should call the IVehicleSpeedSubscriber interface functions on either signal emit or property change.
 * You can use IVehicleSpeedSubscriber class to implement clients of the IVehicleSpeed or the network adapter - see Olink Server and Client example.
 */
class CPP_VEHICLE_SPEED_EXPORT IVehicleSpeedSubscriber
{
public:
    virtual ~IVehicleSpeedSubscriber() = default;
    /**
    * Called by the IVehicleSpeedPublisher when Speed value has changed if subscribed for the Speed change.
    * @param Speed Vehicle speed in kilometers per hour
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual void onSpeedChanged(float Speed) = 0;
};

/** Callback for changes of Speed */
using VehicleSpeedSpeedPropertyCb = std::function<void(float Speed)>;


/**
 * The IVehicleSpeedPublisher provides an api for clients to subscribe to or unsubscribe from a signal emission 
 * or a property change.
 * Implement this interface to keep track of clients of your IVehicleSpeed implementation.
 * The publisher provides two independent methods of subscription
 *  - subscribing with a IVehicleSpeedSubscriber objects - for all of the changes
 *  - subscribing any object for single type of change property or a signal
 * The publish functions needs to be called by implementation of the IIVehicleSpeed on each state changed or signal emitted
 * to notify all the subscribers about this change.
 */
class CPP_VEHICLE_SPEED_EXPORT IVehicleSpeedPublisher
{
public:
    virtual ~IVehicleSpeedPublisher() = default;

    /**
    * Use this function to subscribe for any change of the VehicleSpeed.
    * Subscriber will be informed of any emitted signal and any property changes.
    * This is parallel notification system to single subscription. If you will subscribe also for a single change
    * your subscriber will be informed twice about that change, one for each subscription mechanism.
    * @param IVehicleSpeedSubscriber which is subscribed in this function to any change of the VehicleSpeed.
    */
    virtual void subscribeToAllChanges(IVehicleSpeedSubscriber& subscriber) = 0;
    /**
    * Use this function to remove subscription to all of the changes of the VehicleSpeed.
    * Not all subscriptions will be removed, the ones made separately for single signal or property change stay intact.
    * Make sure to remove them.
    * @param IVehicleSpeedSubscriber which subscription for any change of the VehicleSpeed is removed.
    */
    virtual void unsubscribeFromAllChanges(IVehicleSpeedSubscriber& subscriber) = 0;

    /**
    * Use this function to subscribe for Speed value changes.
    * If your subscriber uses subscription with IVehicleSpeedSubscriber interface, you will get two notifications, one for each subscription mechanism.
    * @param VehicleSpeedSpeedPropertyCb callback that will be executed on each change of the property.
    * Make sure to remove subscription before the callback becomes invalid.
    * @return subscription token for the subscription removal.
    *
    * @warning the subscribed function shall not be blocking and must return immediately!
    */
    virtual long subscribeToSpeedChanged(VehicleSpeedSpeedPropertyCb callback) = 0;
    /**
    * Use this function to unsubscribe from Speed property changes.
    * If your subscriber uses subscription with IVehicleSpeedSubscriber interface, you will be still informed about this change,
    * as those are two independent subscription mechanisms.
    * @param subscription token received on subscription.
    */
    virtual void unsubscribeFromSpeedChanged(long handleId) = 0;

    /**
    * Publishes the property changed to all subscribed clients.
    * Needs to be invoked by the VehicleSpeed implementation when property Speed changes.
    * @param The new value of Speed.
    * Vehicle speed in kilometers per hour
    */
    virtual void publishSpeedChanged(float Speed) const = 0;
};


} // namespace VehicleSpeed
} // namespace Cpp
