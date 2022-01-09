#ifndef TTGO_SERIAL_H
#define TTGO_SERIAL_H

#include <QString>
#include <QSerialPort>
#include <QWidget>

typedef struct GpsData{

    long altitulde_mm = 0;
    uint32_t latitude_mdeg = 0;
    uint32_t longitude_mdeg = 0;

    uint8_t hourGPS = 0;
    uint8_t minuteGPS = 0;
    uint8_t secondGPS = 0;

    uint8_t gpsRun = 0;

}GpsData;

typedef struct Bmp280{

    float temp = 0;
    float pres = 0;

    uint8_t bmp280Run = 0;

}Bmp280;

typedef struct Ds18b20{

    float tempMotor = 0;
    uint8_t ds18B20Run = 0;

}Ds18b20;

typedef struct Ds3231S{

    uint8_t secondRTC;
    uint8_t minuteRTC;
    uint8_t hourRTC;

    uint8_t ds3231sRun = 0;

}Ds3231;

typedef struct Mpu6050{

    float gyroX = 0;
    float gyroY = 0;
    float gyroZ = 0;
    float AccX = 0;
    float AccY = 0;
    float AccZ = 0;

    uint8_t mpu6050Run = 0;

}Mpu6050;

typedef struct AllData{

    GpsData gpsVar;
    Bmp280 bmp280Var;
    Ds18b20 ds18b20Var;
    Ds3231 ds3231Var;
    Mpu6050 mpu6050Var;

    uint8_t seqMesPhase = 0;
    uint8_t seqMesMotor = 0;

    float RSSI = 0;

}AllData;

class TTGO_serial: public QWidget
{
    Q_OBJECT
public:
    TTGO_serial(QWidget *parent = nullptr);

    bool isConnected() const;
    void connectCOM(const QString&);

    AllData getData();

signals :
    void error(QString error);
    void started();
    void stoped();
    void connectedCOM();

    void newData();

private:
    QSerialPort *_serial;
    QByteArray _datas;

    AllData _m_data;

    void processCommand();
    void dataConvert(const QByteArray byteArr);
};

#endif // TTGO_SERIAL_H
