#pragma once

#include "vehicle_speed/generated/api/vehicle_speed.h"


namespace Cpp
{
namespace VehicleSpeed
{

/**
* A helper structure for implementations of VehicleSpeed. Stores all the properties.
*/
struct VehicleSpeedData
{
    float m_Speed {0.0f};
};

}
}