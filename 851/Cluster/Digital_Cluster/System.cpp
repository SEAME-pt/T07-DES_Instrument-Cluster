#include "System.h"

System::System(QObject *parent)
    : QObject{parent},
    m_speed("0"),
    m_batteryPer("0"),
    m_headLights("false"),
    m_brakeLight("false"),
    m_turnLightLeft("false"),
    m_turnLightRight("false"),
    m_emergencyLights("false"),
    m_totalDistance("0")
{}


QString System::speed() const
{
    return m_speed;
}

void System::setSpeed(const QString &newSpeed)
{
    if (m_speed == newSpeed)
        return;
    m_speed = newSpeed;
    emit speedChanged();
}

QString System::batteryPer() const
{
    return m_batteryPer;
}

void System::setBatteryPer(const QString &newBatteryPer)
{
    if (m_batteryPer == newBatteryPer)
        return;
    m_batteryPer = newBatteryPer;
    emit batteryPerChanged();
}

QString System::headLights() const
{
    return m_headLights;
}

void System::setHeadLights(const QString &newHeadLights)
{
    if (m_headLights == newHeadLights)
        return;
    m_headLights = newHeadLights;
    emit headLightsChanged();
}

QString System::brakeLight() const
{
    return m_brakeLight;
}

void System::setBrakeLight(const QString &newBrakeLight)
{
    if (m_brakeLight == newBrakeLight)
        return;
    m_brakeLight = newBrakeLight;
    emit brakeLightChanged();
}

QString System::turnLightLeft() const
{
    return m_turnLightLeft;
}

void System::setTurnLightLeft(const QString &newTurnLightLeft)
{
    if (m_turnLightLeft == newTurnLightLeft)
        return;
    m_turnLightLeft = newTurnLightLeft;
    emit turnLightLeftChanged();
}

QString System::turnLightRight() const
{
    return m_turnLightRight;
}

void System::setTurnLightRight(const QString &newTurnLightRight)
{
    if (m_turnLightRight == newTurnLightRight)
        return;
    m_turnLightRight = newTurnLightRight;
    emit turnLightRightChanged();
}

QString System::emergencyLights() const
{
    return m_emergencyLights;
}

void System::setEmergencyLights(const QString &newEmergencyLights)
{
    if (m_emergencyLights == newEmergencyLights)
        return;
    m_emergencyLights = newEmergencyLights;
    emit emergencyLightsChanged();
}

QString System::totalDistance() const
{
    return m_totalDistance;
}

void System::setTotalDistance(const QString &newTotalDistance)
{
    if (m_totalDistance == newTotalDistance)
        return;
    m_totalDistance = newTotalDistance;
    emit totalDistanceChanged();
}
