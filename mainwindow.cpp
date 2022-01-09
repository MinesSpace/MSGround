#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _timer_data(new QTimer)
{
    ui->setupUi(this);

    connect(ui->ToolZone_wdg, &ToolZone::plotCommand, ui->PlotZone_wdg->plot1(), &Plot::newCommand);
    //connect(_timer_data, &QTimer::timeout, this, &MainWindow::refreshData);

    //ui->PlotZone_wdg->plot1()->enableCurve(SPEED);
    ui->PlotZone_wdg->plot1()->enableCurve(ALTITUDE);

    //ui->PlotZone_wdg->plot2()->enableCurve(ACCELERO_X);
    //ui->PlotZone_wdg->plot2()->enableCurve(ACCELERO_Y);
    ui->PlotZone_wdg->plot1()->enableCurve(ACCELERO_Z);

    ui->PlotZone_wdg->plot2()->enableCurve(GYRO_X);
    ui->PlotZone_wdg->plot2()->enableCurve(GYRO_Y);

    //ui->PlotZone_wdg->plot2()->enableCurve(GYRO_Z);

    //ui->PlotZone_wdg->plot()->addLinePlot("test");
    //ui->PlotZone_wdg->plot()->appendData(0, QPointF(0, 0));
    //ui->PlotZone_wdg->plot()->appendData(0, QPointF(1, 2));

    //QString link = "https://www.google.fr/maps/@48.8556087,2.3324398,737m/data=!3m1!1e3";
    //QDesktopServices::openUrl(QUrl(link));

    datasave = new DataSave;

    datasave->initFile(false);

    _serial = new TTGO_serial(this);

    _serial->connectCOM("COM11");

    connect(_serial, &TTGO_serial::newData, this, &MainWindow::refreshData);

    //serial = new SerialPort();

    //connect(serial, &SerialPort::serialOpenned, this, &MainWindow::connected);
    //connect(serial, &SerialPort::errorEmit, this, &MainWindow::error);

    //serial->run();
    //serial->openSerial("COM11");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionStart_chrono_triggered()
{
    ui->TimeZone_wdg->startChrono();
}

void MainWindow::on_actionStop_chrono_triggered()
{
    ui->TimeZone_wdg->stopChrono();
}

void MainWindow::on_actionReset_chrono_triggered()
{
    ui->TimeZone_wdg->resetChrono();
}

void MainWindow::on_actionGo_to_Australia_triggered()
{
    ui->MapZone_wdg->setPosition(-27.6835, 128.0649);
}

void MainWindow::on_actionGo_to_troducdumonde_triggered()
{
    ui->MapZone_wdg->setPosition(43.2184361, -0.047333333);
}

void MainWindow::on_actionGo_to_plusBelleVilleDuMonde_triggered()
{
    ui->MapZone_wdg->setPosition(43.601846, 1.465393);
}

void MainWindow::on_actionNext_Succes_triggered()
{
    ui->ActionZone_wdg->nextStep(true);
}

void MainWindow::on_actionNext_Fail_triggered()
{
    ui->ActionZone_wdg->nextStep(false);
}

void MainWindow::on_actionReset_triggered()
{
    ui->ActionZone_wdg->resetStep();
}

void MainWindow::connected()
{
    ui->ToolZone_wdg->addConsoleText("->Serial : Connected");
}
void MainWindow::error(QString errorString)
{
    ui->ToolZone_wdg->addConsoleText("->Serial Error : " + errorString);
}

void MainWindow::refreshData()
{
    AllData datas = _serial->getData();

    int time = datas.ds3231Var.secondRTC + datas.ds3231Var.minuteRTC*60 + datas.ds3231Var.hourRTC*3600;

    Gps_coord gps_coord;
    Sensor_measure sensor_measure;

    gps_coord.lattitude = datas.gpsVar.latitude_mdeg / 1000000.0000000;
    gps_coord.longitude = datas.gpsVar.longitude_mdeg / 1000000.0000000;
    sensor_measure.altitude = datas.gpsVar.altitulde_mm/1000;

    sensor_measure.imu.acc_x = datas.mpu6050Var.AccX;
    sensor_measure.imu.acc_y = datas.mpu6050Var.AccY;
    sensor_measure.imu.acc_z = datas.mpu6050Var.AccZ;

    sensor_measure.imu.gyro_x = datas.mpu6050Var.gyroX;
    sensor_measure.imu.gyro_y = datas.mpu6050Var.gyroY;
    sensor_measure.imu.gyro_z = datas.mpu6050Var.gyroZ;

    sensor_measure.temp_motor = datas.ds18b20Var.tempMotor;
    sensor_measure.temp_rack = datas.bmp280Var.temp;
    sensor_measure.rssi = datas.RSSI;

    sensor_measure.time_ms = time;

    //sensor_measure.altitude = datas.bmp280Var.pres;
    if (compteur >= 15)
    {
        ui->MapZone_wdg->setPosition(gps_coord.lattitude, gps_coord.longitude);
        compteur = 0;
    }
    else
    {
        compteur++;
    }
    ui->ToolZone_wdg->setgps(QString::number(gps_coord.lattitude) + " " + QString::number(gps_coord.longitude));


    ui->PlotZone_wdg->plot1()->appendData(ALTITUDE, QPointF(time, sensor_measure.altitude));
    ui->PlotZone_wdg->plot2()->appendData(GYRO_X, QPointF(time, sensor_measure.imu.gyro_x));
    ui->PlotZone_wdg->plot2()->appendData(GYRO_Y, QPointF(time, sensor_measure.imu.gyro_y));
    ui->PlotZone_wdg->plot1()->appendData(ACCELERO_Z, QPointF(time, sensor_measure.imu.acc_z));
    qDebug() << "DATAS :" << time << sensor_measure.altitude;

    if (datas.seqMesPhase > _etat_seq)
    {
        ui->ActionZone_wdg->nextStep(true);
        _etat_seq++;
    }

    if (sensor_measure.altitude > _max_altitude)
    {
        _max_altitude = sensor_measure.altitude;
        ui->ToolZone_wdg->setMaxAltitude(_max_altitude);
    }

    ui->ToolZone_wdg->setRssi(datas.RSSI);
    ui->ToolZone_wdg->setRTC(time);


    datasave->append(gps_coord, sensor_measure);
}
