#ifndef TIMEZONE_H
#define TIMEZONE_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

#include <QDebug>

namespace
{
    constexpr int TICKER_PERIOD_MS = 200;
}

namespace Ui {
class TimeZone;
}

class TimeZone : public QWidget
{
    Q_OBJECT

public:
    explicit TimeZone(QWidget *parent = nullptr);
    ~TimeZone();

    void startChrono();
    void stopChrono();
    void resetChrono();

    int getChrono_ms();

private:
    Ui::TimeZone *ui;

    QTimer *_ticker;

    int _chrono=0;
    bool _isChronoActivated = false;

    void refreshHour();
    void refreshChrono();
};

#endif // TIMEZONE_H
