#include <memory>
#include "catch2/catch.hpp"
#include "vehicle_speed/implementation/vehiclespeed.h"

using namespace Cpp::VehicleSpeed;
TEST_CASE("Testing VehicleSpeed", "[VehicleSpeed]"){
    std::unique_ptr<IVehicleSpeed> testVehicleSpeed = std::make_unique<VehicleSpeed>();
    // setup your test
    SECTION("Test property Speed") {
        // Do implement test here
        testVehicleSpeed->setSpeed(0.0f);
        REQUIRE( testVehicleSpeed->getSpeed() == Approx( 0.0f ) );
    }
}
