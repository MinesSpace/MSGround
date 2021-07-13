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

    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(10);
    _chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTickCount(10);
    _chart->addAxis(axisY, Qt::AlignLeft);

    QStringList title;
    title << SPEED_TTTLE->toUtf8() <<
             ALTITUDE_TITLE->toUtf8() <<
             ACCELERO_X_TITLE->toUtf8() <<
             ACCELERO_Y_TITLE->toUtf8() <<
             ACCELERO_Z_TITLE->toUtf8();

    for (int i=0; i<CURVE_NB; i++)
    {
        PlotLine plotLine;
        plotLine.name = title[i];
        plotLine.serie = new QLineSeries;

        plotLine.serie->attachAxis(axisX);
        plotLine.serie->attachAxis(axisY);
        plotLine.serie->setName(plotLine.name);

        _chart->addSeries(plotLine.serie);
        _lines.append(plotLine);
        _lines[i].serie->setVisible(false);
    }
    _chart->createDefaultAxes();


}

Plot::~Plot()
{
    delete ui;
}
/*
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
}*/
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

void Plot::enableCurve(Curve curve)
{
    _lines[curve].serie->setVisible(true);
}
