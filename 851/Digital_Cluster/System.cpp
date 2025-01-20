#include "System.h"

System::System(QObject *parent)
    : QObject{parent},
    m_speedSensor(0),
    m_batteryPercentage(0)
{}


int System::speedSensor() const
{
    return m_speedSensor;
}

void System::setSpeedSensor(int newSpeedSensor)
{
    if (m_speedSensor == newSpeedSensor)
        return;
    m_speedSensor = newSpeedSensor;
    // qInfo() << "speed no system: " << newSpeedSensor;
    emit speedSensorChanged();
}

int System::batteryPercentage() const
{
    return m_batteryPercentage;
}

void System::setBatteryPercentage(int newBatteryPercentage)
{
    if (m_batteryPercentage == newBatteryPercentage)
        return;
    m_batteryPercentage = newBatteryPercentage;
    emit batteryPercentageChanged();
}
