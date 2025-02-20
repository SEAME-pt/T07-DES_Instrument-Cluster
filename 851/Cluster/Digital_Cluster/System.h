#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QDebug>
#include <QString>

class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(QString batteryPer READ batteryPer WRITE setBatteryPer NOTIFY batteryPerChanged FINAL)
    Q_PROPERTY(QString headLights READ headLights WRITE setHeadLights NOTIFY headLightsChanged FINAL)
    Q_PROPERTY(QString brakeLight READ brakeLight WRITE setBrakeLight NOTIFY brakeLightChanged FINAL)
    Q_PROPERTY(QString turnLightLeft READ turnLightLeft WRITE setTurnLightLeft NOTIFY turnLightLeftChanged FINAL)
    Q_PROPERTY(QString turnLightRight READ turnLightRight WRITE setTurnLightRight NOTIFY turnLightRightChanged FINAL)
    Q_PROPERTY(QString emergencyLights READ emergencyLights WRITE setEmergencyLights NOTIFY emergencyLightsChanged FINAL)
    Q_PROPERTY(QString totalDistance READ totalDistance WRITE setTotalDistance NOTIFY totalDistanceChanged FINAL)

public:
    explicit System(QObject *parent = nullptr);

    QString speed() const;
    void setSpeed(const QString &newSpeed);

    QString batteryPer() const;
    void setBatteryPer(const QString &newBatteryPer);

    QString headLights() const;
    void setHeadLights(const QString &newHeadLights);

    QString brakeLight() const;
    void setBrakeLight(const QString &newBrakeLight);

    QString turnLightLeft() const;
    void setTurnLightLeft(const QString &newTurnLightLeft);

    QString turnLightRight() const;
    void setTurnLightRight(const QString &newTurnLightRight);

    QString emergencyLights() const;
    void setEmergencyLights(const QString &newEmergencyLights);

    QString totalDistance() const;
    void setTotalDistance(const QString &newTotalDistance);

signals:

    void speedChanged();

    void batteryPerChanged();

    void headLightsChanged();

    void brakeLightChanged();

    void turnLightLeftChanged();

    void turnLightRightChanged();

    void emergencyLightsChanged();

    void totalDistanceChanged();

private:

    QString m_speed;
    QString m_batteryPer;
    QString m_headLights;
    QString m_brakeLight;
    QString m_turnLightLeft;
    QString m_turnLightRight;
    QString m_emergencyLights;
    QString m_totalDistance;
    
};

#endif // SYSTEM_H
