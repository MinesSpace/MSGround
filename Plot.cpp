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

    //_chart->setAnimationOptions(QChart::AllAnimations);

    _chartView = new QChartView(_chart);
    _chartView->setRenderHint(QPainter::Antialiasing);
    _chartView->setUpdatesEnabled(true);

    ui->Plot_Layout->addWidget(_chartView);

    axisX = new QValueAxis;
    axisX->setMin(0);
    axisX->setMax(240);
    axisX->setTickCount(10);
    _chart->addAxis(axisX, Qt::AlignBottom);

    axisY = new QValueAxis;
    axisY->setTickCount(10);
    _chart->addAxis(axisY, Qt::AlignLeft);

    axisY2 = new QValueAxis;
    axisY2->setTickCount(10);
    _chart->addAxis(axisY2, Qt::AlignRight);

    QStringList title;
    title << SPEED_TTTLE->toUtf8() <<
             ALTITUDE_TITLE->toUtf8() <<
             ACCELERO_X_TITLE->toUtf8() <<
             ACCELERO_Y_TITLE->toUtf8() <<
             ACCELERO_Z_TITLE->toUtf8() <<
             GYRO_X_TITLE->toUtf8() <<
             GYRO_Y_TITLE->toUtf8() <<
             GYRO_Z_TITLE->toUtf8();

    for (int i=0; i<CURVE_NB; i++)
    {

        PlotLine plotLine;
        plotLine.name = title[i];
        plotLine.serie = new QLineSeries;
        _chart->addSeries(plotLine.serie);

        switch (i)
        {

        case SPEED:
            plotLine.serie->attachAxis(axisX);
            plotLine.serie->attachAxis(axisY);
            break;

        case ALTITUDE:
            plotLine.serie->attachAxis(axisX);
            plotLine.serie->attachAxis(axisY);
            break;

        case ACCELERO_X:
            plotLine.serie->attachAxis(axisX);
            plotLine.serie->attachAxis(axisY);
            break;

        case ACCELERO_Y:
            plotLine.serie->attachAxis(axisX);
            plotLine.serie->attachAxis(axisY);
            break;

        case ACCELERO_Z:
            plotLine.serie->attachAxis(axisX);
            plotLine.serie->attachAxis(axisY2);
            break;

        case GYRO_X:
            plotLine.serie->attachAxis(axisX);
            plotLine.serie->attachAxis(axisY2);
            break;

        case GYRO_Y:
            plotLine.serie->attachAxis(axisX);
            plotLine.serie->attachAxis(axisY2);
            break;

        case GYRO_Z:
            plotLine.serie->attachAxis(axisX);
            plotLine.serie->attachAxis(axisY2);
            break;

        default:
            break;

        }

        plotLine.serie->setName(plotLine.name);
        _lines.append(plotLine);
        _lines[i].serie->setVisible(false);

    }
    //_chart->createDefaultAxes();

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
    _chart->axisX(_lines[index].serie)->setMax(point.x() + 50);

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
    switch (curve)
    {

    case SPEED:
        _chart->axisY(_lines[curve].serie)->setMin(0);
        _chart->axisY(_lines[curve].serie)->setMax(0);
        break;

    case ALTITUDE:
        _chart->axisY(_lines[curve].serie)->setMin(0);
        _chart->axisY(_lines[curve].serie)->setMax(2500);
        break;

    case ACCELERO_X:
        _chart->axisY(_lines[curve].serie)->setMin(-16);
        _chart->axisY(_lines[curve].serie)->setMax(16);
        break;

    case ACCELERO_Y:
        _chart->axisY(_lines[curve].serie)->setMin(-16);
        _chart->axisY(_lines[curve].serie)->setMax(16);
        break;

    case ACCELERO_Z:
        _chart->axisY(_lines[curve].serie)->setMin(-16);
        _chart->axisY(_lines[curve].serie)->setMax(16);
        break;

    case GYRO_X:
        _chart->axisY(_lines[curve].serie)->setMin(-180);
        _chart->axisY(_lines[curve].serie)->setMax(180);
        break;

    case GYRO_Y:
        _chart->axisY(_lines[curve].serie)->setMin(-180);
        _chart->axisY(_lines[curve].serie)->setMax(180);
        break;

    case GYRO_Z:
        _chart->axisY(_lines[curve].serie)->setMin(-180);
        _chart->axisY(_lines[curve].serie)->setMax(180);
        break;

    default:
        break;

    }

    _lines[curve].serie->setVisible(true);

}
