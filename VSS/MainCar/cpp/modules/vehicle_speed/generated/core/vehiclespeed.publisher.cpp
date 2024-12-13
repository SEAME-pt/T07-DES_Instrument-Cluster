

#include "vehicle_speed/generated/core/vehiclespeed.publisher.h"
#include <algorithm>


using namespace Cpp::VehicleSpeed;

void VehicleSpeedPublisher::subscribeToAllChanges(IVehicleSpeedSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found == m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.push_back(std::reference_wrapper<IVehicleSpeedSubscriber>(subscriber));
    }
}

void VehicleSpeedPublisher::unsubscribeFromAllChanges(IVehicleSpeedSubscriber& subscriber)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_allChangesSubscribersMutex);
    auto found = std::find_if(m_allChangesSubscribers.begin(), m_allChangesSubscribers.end(),
                        [&subscriber](const auto element){return &(element.get()) == &subscriber;});
    if (found != m_allChangesSubscribers.end())
    {
        m_allChangesSubscribers.erase(found);
    }
}

long VehicleSpeedPublisher::subscribeToSpeedChanged(VehicleSpeedSpeedPropertyCb callback)
{
    auto handleId = m_speedChangedCallbackNextId++;
    std::unique_lock<std::shared_timed_mutex> lock(m_speedCallbacksMutex);
    m_speedCallbacks[handleId] = callback;
    return handleId;
}

void VehicleSpeedPublisher::unsubscribeFromSpeedChanged(long handleId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_speedCallbacksMutex);
    m_speedCallbacks.erase(handleId);
}

void VehicleSpeedPublisher::publishSpeedChanged(float Speed) const
{
    std::shared_lock<std::shared_timed_mutex> allChangesSubscribersLock(m_allChangesSubscribersMutex);
    const auto allChangesSubscribers = m_allChangesSubscribers;
    allChangesSubscribersLock.unlock();
    for(const auto& subscriber: allChangesSubscribers)
    {
        subscriber.get().onSpeedChanged(Speed);
    }
    std::shared_lock<std::shared_timed_mutex> speedCallbacksLock(m_speedCallbacksMutex);
    const auto speedCallbacks = m_speedCallbacks;
    speedCallbacksLock.unlock();
    for(const auto& callbackEntry: speedCallbacks)
    {
        if(callbackEntry.second)
        {
            callbackEntry.second(Speed);
        }
    }
}

