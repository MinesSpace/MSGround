#ifndef DATASAVE_H
#define DATASAVE_H

#include <QVector>
#include <QPointF>

struct Gps_coord
{
    double lattitude;
    double longitude;
    int time_ms;
};

struct Imu
{
    int acc_x;
    int acc_y;
    int acc_z;

    int gyro_x;
    int gyro_y;
    int gyro_z;
};

struct Sensor_measure
{
    double temp_rack;
    double temp_motor;

    double altitude;
    double speed;

    Imu imu;

    int time_ms;
};

class DataSave
{
public:
    DataSave();

    void append(Gps_coord gps_coord, Sensor_measure sensor_measure);

    Gps_coord getGps(int index);
    Sensor_measure getSensor(int index);

private:

    QVector<Gps_coord> _gps_coord;
    QVector<Sensor_measure> _sensor_mesure;

};

#endif // DATASAVE_H
