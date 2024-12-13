

#include "vehicle_speed/generated/core/vehiclespeed.threadsafedecorator.h"

using namespace Cpp::VehicleSpeed;
VehicleSpeedThreadSafeDecorator::VehicleSpeedThreadSafeDecorator(std::shared_ptr<IVehicleSpeed> impl)
    : m_impl(impl)
{
}
void VehicleSpeedThreadSafeDecorator::setSpeed(float Speed)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_speedMutex);
    m_impl->setSpeed(Speed);
}

float VehicleSpeedThreadSafeDecorator::getSpeed() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_speedMutex);
    return m_impl->getSpeed();
}

IVehicleSpeedPublisher& VehicleSpeedThreadSafeDecorator::_getPublisher() const
{
    return m_impl->_getPublisher();
}