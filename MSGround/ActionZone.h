#ifndef ACTIONZONE_H
#define ACTIONZONE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include <QPointF>
#include <QTimer>
#include <QStringList>
#include <QGraphicsTextItem>
#include <QFont>

#include <QDebug>

namespace
{
    Q_GLOBAL_STATIC_WITH_ARGS(const QString, SCHEMA, ("O-O--O-O-O----O-O"));

    QStringList SCHEMA_TXT = {"IDLE",
                              "LIFT OFF",
                              "APOGEE",
                              "PARACHUTE",
                              "NOMINAL",
                              "TOUCH DOWN",
                              "IDLE"
                             };

    constexpr char STEP = 'O';
    constexpr char LINE = '-';

    constexpr int POINT_SIZE = 60;
    constexpr int POINT_PEN_WIDTH = 5;

    constexpr int TEXT_Y = 140;
    constexpr int TEXT_SIZE = 15;

    constexpr int LINE_LENGTH = 40;
    constexpr int LINE_WIDTH = 4;
    constexpr int LINE_PEN_WIDTH = 2;

    constexpr int POSITION_ZERO_X = 0;
    constexpr int POSITION_ZERO_Y = 200;

    constexpr int SPACE = 15;
}

namespace Ui {
class ActionZone;
}

class ActionZone : public QWidget
{
    Q_OBJECT

public:
    explicit ActionZone(QWidget *parent = nullptr);
    ~ActionZone();

    void nextStep(bool succes = true);
    void resetStep();

private:
    Ui::ActionZone *_ui;

    QGraphicsScene* _scene;

    QVector<QGraphicsEllipseItem*> _ellipseItem;
    QVector<QGraphicsRectItem*> _rectItem;
    QVector<QGraphicsTextItem*> _textItem;

    QPointF _cursor;

    QPen _penPoint;
    QPen _penLine;
    QFont _textFont;

    QPen _penSuccess;
    QPen _penFail;

    int _current_step=0;


private slots :

    void fitIn();
};

#endif // ACTIONZONE_H
