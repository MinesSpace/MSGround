#include "Plot.h"
#include "ui_Plot.h"


#include <QDebug>


Plot::Plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot),
    _chartView(nullptr),
    _chart(new QChart)
{
    ui->setupUi(this);

    _chart->setAnimationOptions(QChart::AllAnimations);

    _chartView = new QChartView(_chart);
    _chartView->setRenderHint(QPainter::Antialiasing);
    _chartView->setUpdatesEnabled(true);

    ui->Plot_Layout->addWidget(_chartView);

    for (int i=0; i<CURVE_NB; i++)
    {

    }
}

Plot::~Plot()
{
    delete ui;
}

void Plot::addLinePlot(QString name)
{
    PlotLine plotLine;
    plotLine.name = name;
    plotLine.serie = new QLineSeries;

    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(10);
    _chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTickCount(10);
    _chart->addAxis(axisY, Qt::AlignLeft);

    plotLine.serie->attachAxis(axisX);
    plotLine.serie->attachAxis(axisY);

    _lines.append(plotLine);
    _chart->addSeries(plotLine.serie);
    //_chart->createDefaultAxes();
}
void Plot::appendData(int index, QPointF point)
{
    qDebug() << "append";
    _lines[index].serie->append(point);

}

void Plot::newCommand(QString command)
{
    if (command.at(6) == 'A')
    {
        QPointF point(command.at(8).unicode(), command.split("")[12].toInt());
        _lines[command.split("")[8].toInt()].serie->append(point);

        qDebug() << command.at(6) << command.at(8).unicode() << command.at(10).unicode() << command.at(12).unicode();
    }
}
