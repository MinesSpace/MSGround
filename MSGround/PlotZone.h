#ifndef PLOTZONE_H
#define PLOTZONE_H

#include <QWidget>
#include "Plot.h"

namespace Ui {
class PlotZone;
}

class PlotZone : public QWidget
{
    Q_OBJECT

public:
    explicit PlotZone(QWidget *parent = nullptr);
    ~PlotZone();

    Plot* plot1();
    Plot* plot2();

private:
    Ui::PlotZone *ui;
};

#endif // PLOTZONE_H
