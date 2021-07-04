#include "PlotZone.h"
#include "ui_PlotZone.h"


PlotZone::PlotZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotZone)
{
    ui->setupUi(this);
}

PlotZone::~PlotZone()
{
    delete ui;
}

Plot* PlotZone::plot()
{
    return ui->plot;
}
