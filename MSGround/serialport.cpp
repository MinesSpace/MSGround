#include "serialport.h"

Q_DECLARE_METATYPE(QSerialPort::SerialPortError);
Q_DECLARE_METATYPE(SerialPort::Settings);

SerialPort::SerialPort() {
}

SerialPort::~SerialPort() {
    delete m_serial;
    delete m_settingsPort;
}

bool SerialPort::openSerial()
{
    m_serial->setPortName(m_settingsPort->name);
    m_serial->setBaudRate(m_settingsPort->baudRate);
    m_serial->setDataBits(m_settingsPort->dataBits);
    m_serial->setParity(m_settingsPort->parity);
    m_serial->setStopBits(m_settingsPort->stopBits);
    m_serial->setFlowControl(m_settingsPort->flowControl);

    m_serial->setReadBufferSize(62);

    if (m_serial->open(QIODevice::ReadOnly)) {
        m_serial->clear(QSerialPort::AllDirections);
        emit SerialPort::serialOpenned(this->settingsInfo());
        return true;
    }
    else
        return false;
}

bool SerialPort::openSerial(QString name)
{
    m_serial->setPortName(name);
    m_serial->setBaudRate(m_settingsPort->baudRate);
    m_serial->setDataBits(m_settingsPort->dataBits);
    m_serial->setParity(m_settingsPort->parity);
    m_serial->setStopBits(m_settingsPort->stopBits);
    m_serial->setFlowControl(m_settingsPort->flowControl);

    m_serial->setReadBufferSize(62);

    if (m_serial->open(QIODevice::ReadOnly)) {
        m_serial->clear(QSerialPort::AllDirections);
        emit SerialPort::serialOpenned(this->settingsInfo());
        return true;
    }
    else
        return false;
}

void SerialPort::closeSerial()
{
    if (m_serial->isOpen()) {
        m_serial->clear(QSerialPort::AllDirections);
        m_serial->close();
        emit SerialPort::serialClosed();
    }
}

void SerialPort::handleError(QSerialPort::SerialPortError error)
{
    qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] handleError";
    if (error != QSerialPort::NoError) {
        m_serialRun = false;
        qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] emit errorEmit";
        emit SerialPort::errorEmit(m_serial->errorString());
    }
}

QString SerialPort::serialError() const
{
    return m_serial->errorString();
}

bool SerialPort::checkOpenSerial() const
{
    return m_serial->isOpen();
}

SerialPort::Settings SerialPort::settingsInfo() const
{
    return *m_settingsPort;
}

void SerialPort::settingUpdate(SerialPort::Settings settingPort)
{
    qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] settingUpdate";
    *m_settingsPort = settingPort;
}

void SerialPort::readingData() {

    if(m_serial->bytesAvailable() >= 62) {
        QByteArray data = m_serial->read(62);

        emit dataBrutEmit(true, data);
        qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] Data received : " << Qt::hex << data.toHex();

        dataConvert(data);
    }
    else {
        QThread::msleep(1);
        qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] Frame not complete !";
    }

    /*else {
        //emit dataEmit(false, "");
        qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] Timeout error !";
    }*/
}

void SerialPort::setSerialRun(bool onoff) {
    m_serialRun = onoff;
}

void SerialPort::run() {

    m_serial = new QSerialPort;
    m_settingsPort = new Settings;

    m_serialRun = false;

    // Register types for connect
    qRegisterMetaType<QSerialPort::SerialPortError>();
    qRegisterMetaType<SerialPort::Settings>();

    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialPort::handleError);

    qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] " << QThread::currentThread();
    while(1) {
        if(m_serialRun) {
            if(this->openSerial()) {
                qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] Serial oppened";
            }
            else {
                qDebug() << "[" << QDateTime::currentDateTime().toString("dd-MM-yyyy_HH.mm.ss") << "][SERIAL] Serial failed";
                m_serialRun = false;
            }
            while(m_serialRun) {
                readingData();
            }
            this->closeSerial();
        }
        QThread::msleep(10);
    }
}

void SerialPort::dataConvert(const QByteArray byteArr){

    //GPS

    m_data.gpsVar.latitude_mdeg  = ( (byteArr[1] << 24)
        + (byteArr[2] << 16)
        + (byteArr[3] << 8)
        + (byteArr[4] ) );

    m_data.gpsVar.longitude_mdeg = ( (byteArr[5] << 24)
        + (byteArr[6] << 16)
        + (byteArr[7] << 8)
        + (byteArr[8] ) );

    m_data.gpsVar.altitulde_mm = ( (byteArr[9] << 24)
        + (byteArr[10] << 16)
        + (byteArr[11] << 8)
        + (byteArr[12] ) );

    m_data.gpsVar.hourGPS = byteArr[13];
    m_data.gpsVar.minuteGPS = byteArr[14];
    m_data.gpsVar.secondGPS = byteArr[15];
    m_data.gpsVar.gpsRun = byteArr[16];

    //BMP280

    int bmp280Temp =  ( (byteArr[17] << 24)
         + (byteArr[18] << 16)
         + (byteArr[19] << 8)
         + (byteArr[20] ) );

    m_data.bmp280Var.temp = (float) bmp280Temp / 1000.000;

    int bmp280Pres =  ( (byteArr[21] << 24)
          + (byteArr[22] << 16)
          + (byteArr[23] << 8)
          + (byteArr[24] ) );

    m_data.bmp280Var.pres = (float) bmp280Pres / 1000.000;

    m_data.bmp280Var.bmp280Run = byteArr[25];

    //DS18B20

    int ds18b20Temp =  ( (byteArr[26] << 24)
          + (byteArr[27] << 16)
          + (byteArr[28] << 8)
          + (byteArr[29] ) );

    m_data.ds18b20Var.ds18B20Run = (float) ds18b20Temp / 1000.000 ;

    //MPU6050

    int gyroX = ( (byteArr[30] << 24)
          + (byteArr[31] << 16)
          + (byteArr[32] << 8)
          + (byteArr[33] ) );

    m_data.mpu6050Var.gyroX = (float) gyroX / 1000.000;

    int gyroY = ( (byteArr[34] << 24)
          + (byteArr[35] << 16)
          + (byteArr[36] << 8)
          + (byteArr[37] ) );

    m_data.mpu6050Var.gyroY = (float) gyroY / 1000.000;

    int gyroZ = ( (byteArr[38] << 24)
           + (byteArr[39] << 16)
           + (byteArr[40] << 8)
           + (byteArr[41] ) );

    m_data.mpu6050Var.gyroY = (float) gyroZ / 1000.000;

    int AccX  = ( (byteArr[42] << 24)
            + (byteArr[43] << 16)
            + (byteArr[44] << 8)
            + (byteArr[45] ) );

    m_data.mpu6050Var.AccX  = (float) AccX  / 1000.000;

    int AccY  = ( (byteArr[46] << 24)
            + (byteArr[47] << 16)
            + (byteArr[48] << 8)
            + (byteArr[49] ) );

    m_data.mpu6050Var.AccY  = (float) AccY / 1000.000;

    int AccZ  = ( (byteArr[50] << 24)
            + (byteArr[51] << 16)
            + (byteArr[52] << 8)
            + (byteArr[53] ) );

    m_data.mpu6050Var.AccZ  = (float) AccZ / 1000.000;

    m_data.mpu6050Var.mpu6050Run = byteArr[54];

    //DS3231S

    m_data.ds3231Var.secondRTC = byteArr[55];
    m_data.ds3231Var.minuteRTC = byteArr[56];
    m_data.ds3231Var.hourRTC = byteArr[57];
    m_data.ds3231Var.ds3231sRun = byteArr[58];

    //SEQ

    m_data.seqMes = byteArr[59];

    emit dataEmit(m_data);

}

