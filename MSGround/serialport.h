#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QSemaphore>
#include <QStack>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QThread>
#include <QDateTime>

class SettingsDialog;

class SerialPort : public QThread
{
    Q_OBJECT

public:

    // All struct

    typedef struct GpsData{

        long altitulde_mm = 0;
        long latitude_mdeg = 0;
        long longitude_mdeg = 0;

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

        uint8_t seqMes = 0;

    }AllData;

    struct Settings {
        QString name;
        qint32 baudRate = QSerialPort::Baud115200;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits = QSerialPort::Data8;
        QString stringDataBits;
        QSerialPort::Parity parity = QSerialPort::NoParity;
        QString stringParity;
        QSerialPort::StopBits stopBits = QSerialPort::OneStop;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
        QString stringFlowControl;
    };

    SerialPort();
    ~SerialPort();

    bool openSerial();
    bool openSerial(QString name);
    void handleError(QSerialPort::SerialPortError error);

    void closeSerial();

    bool checkOpenSerial() const;
    Settings settingsInfo() const;
    QString serialError() const;
    void setSerialRun(bool onoff);
    void run() override;

public slots:
    void settingUpdate(SerialPort::Settings settingPort);
    void readingData();

signals:
    void errorEmit(QString);
    void dataBrutEmit(bool receptionChek, QByteArray data = NULL);
    void dataEmit(const AllData data);
    void serialOpenned(SerialPort::Settings p);
    void serialClosed();

private:

    void dataConvert(const QByteArray byteArr);

    Settings *m_settingsPort = nullptr;
    QSerialPort *m_serial = nullptr;

    AllData m_data;
    bool m_serialRun;

    QMutex mut;
};

#endif // SERIALPORT_H
