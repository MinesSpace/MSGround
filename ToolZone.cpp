#include "ToolZone.h"
#include "ui_ToolZone.h"

ToolZone::ToolZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolZone)
{
    ui->setupUi(this);
}

ToolZone::~ToolZone()
{
    delete ui;
}

void ToolZone::on_send_pb_2_clicked()
{
    QString command = ui->command_lbl->text();
    QString answer;

    if (command.at(0) == COMMAND_CHAR)
    {
        if (command.contains(COMMAND_PLOT->toUtf8()))
        {
            answer =  ANSWER_PLOT->toUtf8();
            emit plotCommand(command);
        }
        else
        {
            answer = COMMAND_NOT_FOUND->toUtf8();
        }

    }

    ui->console->setPlainText(ui->console->toPlainText() + "\n" + command + " \n" + answer);
}

void ToolZone::addConsoleText(const QString text)
{
    ui->console->setPlainText(ui->console->toPlainText() + "\n" + text);
}

void ToolZone::setMaxAltitude(int altitude)
{
    ui->altitude_lbl->setText(QString::number(altitude));
}

void ToolZone::setRssi(int rssi)
{
    ui->rssi_lbl->setText(QString::number(rssi));
}

void ToolZone::setRTC(int time)
{
    ui->rtc_lbl->setText(QString::number(time));
}

void ToolZone::setgps(QString gps)
{
    ui->gps_lbl->setText(gps);
}
