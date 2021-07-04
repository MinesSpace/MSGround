#ifndef PLOT_H
#define PLOT_H

#include <QWidget>

#include <QVBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QVector>
#include <QPointF>

QT_CHARTS_USE_NAMESPACE

enum Curve
{
    SPEED,
    ALTITUDE,
    ACCELERO_X,
    ACCELERO_Y,
    ACCELERO_Z,
    CURVE_NB
};

struct PlotLine
{
    QLineSeries *serie;

    QString name;
};

namespace Ui {
class Plot;
}

class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);
    ~Plot();

    void addLinePlot(QString name);
    void appendData(int index, QPointF point);

    void newCommand(QString command);

private:
    Ui::Plot *ui;
    QChartView *_chartView;
    QChart *_chart;
    QVector<PlotLine> _lines;

};

#endif // PLOT_H
