#include "Datasave.h"

#include <QTime>
#include <QFileDialog>

namespace
{
    Q_GLOBAL_STATIC_WITH_ARGS(const QString, DEFAULT_FILENAME, ("C:/Users/paulb/Desktop/CSV_export_"));
    Q_GLOBAL_STATIC_WITH_ARGS(const QString, RETURN_CARRIAGE, (";"));
}

DataSave::DataSave()
{

}

bool DataSave::initFile(bool default_path)
{

    QDate date = QDate::currentDate();

    if (default_path)
    {
        _file.setFileName(DEFAULT_FILENAME->toUtf8() + date.toString("yyyyMMdd - .csv"));
    }
    else
    {

        QString fileName = QFileDialog::getSaveFileName(0, "Save as", date.toString("yyyyMMdd - .csv"),"csv (*.csv)"); // export csv file
        _file.setFileName(fileName);
    }

    if(_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTime currentTime;
        currentTime = QTime::currentTime();

        QTextStream txtStream(&_file);

        txtStream << currentTime.toString("hh:mm:ss:zzz") << RETURN_CARRIAGE->toUtf8();

        txtStream << "Time receive" << RETURN_CARRIAGE->toUtf8()
                  << "Time sent" << RETURN_CARRIAGE->toUtf8()
                  << "Lattitude" << RETURN_CARRIAGE->toUtf8()
                  << "Longitude" << RETURN_CARRIAGE->toUtf8()
                  << "Acc_x" << RETURN_CARRIAGE->toUtf8()
                  << "Acc_y" << RETURN_CARRIAGE->toUtf8()
                  << "Acc_z" << RETURN_CARRIAGE->toUtf8()
                  << "Gyro_x" << RETURN_CARRIAGE->toUtf8()
                  << "Gyro_y" << RETURN_CARRIAGE->toUtf8()
                  << "Gyro_z" << RETURN_CARRIAGE->toUtf8()
                  << "Temp_rack" << RETURN_CARRIAGE->toUtf8()
                  << "Temp_motor" << RETURN_CARRIAGE->toUtf8()
                  << "Altitude" << RETURN_CARRIAGE->toUtf8()
                  << "Speed" << RETURN_CARRIAGE->toUtf8();

        return true;
    }

    return false;

}

void DataSave::append(Gps_coord gps_coord, Sensor_measure sensor_measure)
{
    _gps_coord.append(gps_coord);
    _sensor_mesure.append(sensor_measure);
}

Gps_coord DataSave::getGps(int index)
{
   if (index <= _gps_coord.size())
   {
       return _gps_coord[index];
   }

   return _gps_coord.last();

}

Sensor_measure DataSave::getSensor(int index)
{
    if (index <= _gps_coord.size())
    {
        return _sensor_mesure[index];
    }

    return _sensor_mesure.last();
}

void DataSave::writeData(Gps_coord gps_coord, Sensor_measure sensor_measure)
{
    QTime currentTime;
    currentTime = QTime::currentTime();

    QTextStream txtStream(&_file);

    txtStream << currentTime.toString("hh:mm:ss:zzz") << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.time_ms << RETURN_CARRIAGE->toUtf8()
              << gps_coord.lattitude << RETURN_CARRIAGE->toUtf8()
              << gps_coord.longitude << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.imu.acc_x << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.imu.acc_y << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.imu.acc_z << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.imu.gyro_x << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.imu.gyro_y << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.imu.gyro_z << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.temp_rack << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.temp_motor << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.altitude << RETURN_CARRIAGE->toUtf8()
              << sensor_measure.speed << RETURN_CARRIAGE->toUtf8();
}