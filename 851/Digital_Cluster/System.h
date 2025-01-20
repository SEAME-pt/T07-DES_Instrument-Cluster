#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QDebug>

class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speedSensor READ speedSensor WRITE setSpeedSensor NOTIFY speedSensorChanged FINAL)
    Q_PROPERTY(int batteryPercentage READ batteryPercentage WRITE setBatteryPercentage NOTIFY batteryPercentageChanged FINAL)

public:
    explicit System(QObject *parent = nullptr);

    int speedSensor() const;
    void setSpeedSensor(int newSpeedSensor);

    int batteryPercentage() const;
    void setBatteryPercentage(int newBatteryPercentage);

signals:

    void speedSensorChanged();
    void batteryPercentageChanged();

// public slots:
//     void setSpeedSensor(int newSpeedSensor);
//     void setBatteryPercentage(int newBatteryPercentage);

private:

    int m_speedSensor;
    int m_batteryPercentage;
};

#endif // SYSTEM_H
