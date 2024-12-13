

#include "vehicle_speed/implementation/vehiclespeed.h"
#include "vehicle_speed/generated/core/vehiclespeed.publisher.h"
#include "vehicle_speed/generated/core/vehiclespeed.data.h"

using namespace Cpp::VehicleSpeed;

VehicleSpeed::VehicleSpeed()
    : m_publisher(std::make_unique<VehicleSpeedPublisher>())
{
}
VehicleSpeed::~VehicleSpeed()
{
}

void VehicleSpeed::setSpeed(float Speed)
{
    if (m_data.m_Speed != Speed) {
        m_data.m_Speed = Speed;
        m_publisher->publishSpeedChanged(Speed);
    }
}

float VehicleSpeed::getSpeed() const
{
    return m_data.m_Speed;
}

IVehicleSpeedPublisher& VehicleSpeed::_getPublisher() const
{
    return *m_publisher;
}
