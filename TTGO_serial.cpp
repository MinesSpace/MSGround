#include "TTGO_serial.h"
#include <QDebug>
#include <QTimer>

TTGO_serial::TTGO_serial(QWidget *parent) :
    QWidget(parent)
{
    _serial = new QSerialPort;
    connect(_serial, &QSerialPort::readyRead, this, &TTGO_serial::processCommand);
}

void TTGO_serial::connectCOM(const QString& com)
{
    _serial->setPortName(com);
    _serial->setBaudRate(QSerialPort::Baud115200);
    _serial->setDataBits(QSerialPort::Data8);
    _serial->setParity(QSerialPort::NoParity);
    _serial->setStopBits(QSerialPort::OneStop);
    _serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "PAS CONNECTED";
        emit error("Unable to open port");
        return;
    }
    qDebug() << "CONNECTED";
    emit connectedCOM();
}

void TTGO_serial::processCommand()
{
    QByteArray _dataBuff;

    if (_serial->isOpen())
       {
           _datas.append(_serial->readAll());
           if (_datas.size() != 0)
           {
               qDebug() << " _datas.size" << _datas.size();
               if (_datas[_datas.size() - 1] == '\r')
               {
                   qDebug() << "RECEIVE " << _datas.size();
                   _dataBuff = _datas;
                   dataConvert(_dataBuff);
                   _datas.clear();
               }
            }
      }
}

void TTGO_serial::dataConvert(const QByteArray byteArr)
{
    qDebug() <<byteArr;

    uint8_t test[4];

    //BMP280
    test[0] = byteArr[0];
    test[1] = byteArr[1];
    test[2] = byteArr[2];
    test[3] = byteArr[3];
    memcpy(&_m_data.bmp280Var.temp, &test, 4);

    test[0] = byteArr[4];
    test[1] = byteArr[5];
    test[2] = byteArr[6];
    test[3] = byteArr[7];
    memcpy(&_m_data.bmp280Var.pres, &test, 4);

    _m_data.bmp280Var.bmp280Run = byteArr[8];

     //DS18B20

    test[0] = byteArr[9];
    test[1] = byteArr[10];
    test[2] = byteArr[11];
    test[3] = byteArr[12];
    memcpy(&_m_data.ds18b20Var.ds18B20Run, &test, 4);

    _m_data.ds18b20Var.ds18B20Run = byteArr[13];

     //DS3231S

    _m_data.ds3231Var.hourRTC = byteArr[14];
    _m_data.ds3231Var.minuteRTC = byteArr[15];
    _m_data.ds3231Var.secondRTC = byteArr[16];

    _m_data.ds3231Var.ds3231sRun = byteArr[17];

    //MPU6050

    test[0] = byteArr[18];
    test[1] = byteArr[19];
    test[2] = byteArr[20];
    test[3] = byteArr[21];
    memcpy(&_m_data.mpu6050Var.gyroX, &test, 4);

    test[0] = byteArr[22];
    test[1] = byteArr[23];
    test[2] = byteArr[24];
    test[3] = byteArr[25];
    memcpy(&_m_data.mpu6050Var.gyroY, &test, 4);

    test[0] = byteArr[26];
    test[1] = byteArr[27];
    test[2] = byteArr[28];
    test[3] = byteArr[29];
    memcpy(&_m_data.mpu6050Var.gyroZ, &test, 4);

    test[0] = byteArr[30];
    test[1] = byteArr[31];
    test[2] = byteArr[32];
    test[3] = byteArr[33];
    memcpy(&_m_data.mpu6050Var.AccX, &test, 4);

    test[0] = byteArr[34];
    test[1] = byteArr[35];
    test[2] = byteArr[36];
    test[3] = byteArr[37];
    memcpy(&_m_data.mpu6050Var.AccY, &test, 4);

    test[0] = byteArr[38];
    test[1] = byteArr[39];
    test[2] = byteArr[40];
    test[3] = byteArr[41];
    memcpy(&_m_data.mpu6050Var.AccZ, &test, 4);

    _m_data.mpu6050Var.mpu6050Run = byteArr[42];

    //SEQ

    _m_data.seqMesPhase = byteArr[43];
    _m_data.seqMesMotor = byteArr[44];

    //GPS

    _m_data.gpsVar.latitude_mdeg  = (uint32_t)((byteArr[45] << 24)&0xFF000000);
    _m_data.gpsVar.latitude_mdeg  += (uint32_t)((byteArr[46] << 16)&0xFF0000);
    _m_data.gpsVar.latitude_mdeg  += (uint32_t)((byteArr[47] << 8)&0xFF00);
    _m_data.gpsVar.latitude_mdeg  += (uint32_t)((byteArr[48] << 8)&0xFF);

    //qDebug() << "latitude_mdeg" << _m_data.gpsVar.latitude_mdeg << QString::number(byteArr[45],16) << QString::number(byteArr[46],16) << QString::number(byteArr[47],16) << QString::number(byteArr[48],16);

    _m_data.gpsVar.longitude_mdeg  = (uint32_t)((byteArr[49] << 24)&0xFF000000);
    _m_data.gpsVar.longitude_mdeg  += (uint32_t)((byteArr[50] << 16)&0xFF0000);
    _m_data.gpsVar.longitude_mdeg  += (uint32_t)((byteArr[51] << 8)&0xFF00);
    _m_data.gpsVar.longitude_mdeg  += (uint32_t)((byteArr[52] << 8)&0xFF);

    qDebug() << "longitude_mdeg" << _m_data.gpsVar.longitude_mdeg << QString::number(byteArr[49],16) << QString::number(byteArr[50],16) << QString::number(byteArr[51],16) << QString::number(byteArr[52],16);

    //qDebug() << "longitude_mdeg" << _m_data.gpsVar.longitude_mdeg;

    _m_data.gpsVar.altitulde_mm = ( (byteArr[53] << 24)
        + (byteArr[54] << 16)
        + (byteArr[55] << 8)
        + (byteArr[56] ) );

    _m_data.gpsVar.hourGPS = byteArr[57];
    _m_data.gpsVar.minuteGPS = byteArr[58];
    _m_data.gpsVar.secondGPS = byteArr[59];
    _m_data.gpsVar.gpsRun = byteArr[60];

    test[0] = byteArr[61];
    test[1] = byteArr[62];
    test[2] = byteArr[63];
    test[3] = byteArr[64];

    memcpy(&_m_data.RSSI, &test, 4);

    //emit dataEmit(_m_data);
    emit newData();

}

AllData TTGO_serial::getData()
{
    return _m_data;
}
