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

    if(m_serial->bytesAvailable() >= 65) {
        QByteArray data = m_serial->read(65);

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

    uint8_t test[4];

    //BMP280
    test[0] = byteArr[0];
    test[1] = byteArr[1];
    test[2] = byteArr[2];
    test[3] = byteArr[3];
    memcpy(&data.bmp280Var.temp, &test, 4);

    test[0] = byteArr[4];
    test[1] = byteArr[5];
    test[2] = byteArr[6];
    test[3] = byteArr[7];
    memcpy(&data.bmp280Var.pres, &test, 4);

    data.bmp280Var.bmp280Run = byteArr[8];

     //DS18B20

    test[0] = byteArr[9];
    test[1] = byteArr[10];
    test[2] = byteArr[11];
    test[3] = byteArr[12];
    memcpy(&data.ds18b20Var.ds18B20Run, &test, 4);

    data.ds18b20Var.ds18B20Run = byteArr[13];

     //DS3231S

    data.ds3231Var.hourRTC = byteArr[14];
    data.ds3231Var.minuteRTC = byteArr[15];
    data.ds3231Var.secondRTC = byteArr[16];

    data.ds3231Var.ds3231sRun = byteArr[17];

    //MPU6050

    test[0] = byteArr[18];
    test[1] = byteArr[19];
    test[2] = byteArr[20];
    test[3] = byteArr[21];
    memcpy(&data.mpu6050Var.gyroX, &test, 4);

    test[0] = byteArr[22];
    test[1] = byteArr[23];
    test[2] = byteArr[24];
    test[3] = byteArr[25];
    memcpy(&data.mpu6050Var.gyroY, &test, 4);

    test[0] = byteArr[26];
    test[1] = byteArr[27];
    test[2] = byteArr[28];
    test[3] = byteArr[29];
    memcpy(&data.mpu6050Var.gyroZ, &test, 4);

    test[0] = byteArr[30];
    test[1] = byteArr[31];
    test[2] = byteArr[32];
    test[3] = byteArr[33];
    memcpy(&data.mpu6050Var.AccX, &test, 4);

    test[0] = byteArr[34];
    test[1] = byteArr[35];
    test[2] = byteArr[36];
    test[3] = byteArr[37];
    memcpy(&data.mpu6050Var.AccY, &test, 4);

    test[0] = byteArr[38];
    test[1] = byteArr[39];
    test[2] = byteArr[40];
    test[3] = byteArr[41];
    memcpy(&data.mpu6050Var.AccZ, &test, 4);

    data.mpu6050Var.mpu6050Run = byteArr[42];

    //SEQ

    data.seqMesPhase = byteArr[43];
    data.seqMesMotor = byteArr[44];

    //GPS

    data.gpsVar.latitude_mdeg  = ( (byteArr[45] << 24)
        + (byteArr[46] << 16)
        + (byteArr[47] << 8)
        + (byteArr[48] ) );

    data.gpsVar.longitude_mdeg = ( (byteArr[49] << 24)
        + (byteArr[50] << 16)
        + (byteArr[51] << 8)
        + (byteArr[52] ) );

    data.gpsVar.altitulde_mm = ( (byteArr[53] << 24)
        + (byteArr[54] << 16)
        + (byteArr[55] << 8)
        + (byteArr[56] ) );

    data.gpsVar.hourGPS = byteArr[57];
    m_data.gpsVar.minuteGPS = byteArr[58];
    m_data.gpsVar.secondGPS = byteArr[59];
    m_data.gpsVar.gpsRun = byteArr[60];

    test[0] = byteArr[61];
    test[1] = byteArr[62];
    test[2] = byteArr[63];
    test[3] = byteArr[64];

    memcpy(&data.RSSI, &test, 4);

    emit dataEmit(m_data);

}

