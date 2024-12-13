#include <gtest/gtest.h>
#include "SpeedSensor.hpp"
#include "CANBus.hpp"

// Mock CANBus class for testing purposes (if needed)
class MockCANBus : public CANBus {
public:
    bool receiveMessage(uint32_t& id, std::vector<uint8_t>& data) {
        id = 0x123;
        data = {0x01, 0x02, 0x03, 0x04};
        return true;  // Simulate a successful message reception
    }
};

// Test case for SpeedSensor class
TEST(SpeedSensorTest, InitializationTest) {
    MockCANBus mockBus;
    SpeedSensor sensor(mockBus, 0x123);

    sensor.initialize();

    // You can add more checks here (e.g., mock function verification, logger checks, etc.)
    ASSERT_EQ(sensor.getType(), "SpeedSensor");
}

TEST(SpeedSensorTest, ReadDataTest) {
    MockCANBus mockBus;
    SpeedSensor sensor(mockBus, 0x123);

    sensor.readData();  // Simulate reading data

    ASSERT_TRUE(true);  // For now, just a placeholder
}
