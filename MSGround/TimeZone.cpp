#include "TimeZone.h"
#include "ui_TimeZone.h"

TimeZone::TimeZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeZone),
    _ticker(new QTimer)
{
    ui->setupUi(this);

    connect(_ticker, &QTimer::timeout, this, &TimeZone::refreshHour);
    _ticker->start(TICKER_PERIOD_MS);
}

TimeZone::~TimeZone()
{
    delete ui;
}

void TimeZone::startChrono()
{
    _isChronoActivated = true;
}
void TimeZone::stopChrono()
{
    _isChronoActivated = false;
}

void TimeZone::resetChrono()
{
    _chrono = 0;
    refreshChrono();
}

int TimeZone::getChrono_ms()
{
    return _chrono;
}

void TimeZone::refreshHour()
{
    QDateTime TodayDate = QDateTime::currentDateTime();
    ui->hour_lbl->setText(TodayDate.toString("hh:mm:ss"));

    if (_isChronoActivated)
    {
        _chrono += TICKER_PERIOD_MS;
        refreshChrono();
    }
}

void TimeZone::refreshChrono()
{
    QTime time(0,0,0,0);
    time = time.addMSecs(_chrono);

    ui->time_lbl->setText(time.toString("ss:zz"));
}
