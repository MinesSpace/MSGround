#include "ActionZone.h"
#include "ui_ActionZone.h"

ActionZone::ActionZone(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ActionZone),
    _scene(new QGraphicsScene)
{
    _ui->setupUi(this);
    _ui->graphicsView->setScene(_scene);

    _ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    _ui->graphicsView->setStyleSheet("background: transparent; border: 0px");

    _scene->setSceneRect(0, 0, 1200, 300);

    _cursor.setX(POSITION_ZERO_X);
    _cursor.setY(POSITION_ZERO_Y);

    _penPoint.setBrush(QColorConstants::Black);
    _penPoint.setWidth(POINT_PEN_WIDTH);

    _penLine.setBrush(QColorConstants::Black);
    _penLine.setWidth(LINE_PEN_WIDTH);

    _penSuccess.setBrush(QColorConstants::Green);
    _penSuccess.setWidth(POINT_PEN_WIDTH);

    _penFail.setBrush(QColorConstants::Red);
    _penFail.setWidth(POINT_PEN_WIDTH);

    _textFont.setBold(true);
    _textFont.setWeight(QFont::Black);
    _textFont.setPointSize(TEXT_SIZE);

    int lenght=0;

    for (int i=0; i<(SCHEMA->toUtf8().size()); i++)
    {
        if (SCHEMA->toUtf8().at(i) == STEP)
        {
            _ellipseItem.append(_scene->addEllipse(_cursor.x(), _cursor.y()-POINT_SIZE/2, POINT_SIZE, POINT_SIZE, _penPoint));
            _textItem.append(_scene->addText(SCHEMA_TXT[_ellipseItem.size()-1], _textFont));
            _textItem.last()->setPos(_cursor.x() + POINT_SIZE/2 + _textItem.last()->textWidth()*TEXT_SIZE, TEXT_Y);
            _textItem.last()->setRotation(-45);
            _cursor.setX(_cursor.x() + POINT_SIZE + SPACE);
        }
        else if (SCHEMA->toUtf8().at(i) == LINE)
        {
            if (SCHEMA->toUtf8().at(i+1) == LINE)
            {
                _cursor.setX(_cursor.x() + LINE_LENGTH + SPACE);
                lenght += LINE_LENGTH + SPACE;
            }
            else
            {
                _rectItem.append(_scene->addRect(_cursor.x() - lenght, _cursor.y() - LINE_WIDTH/2, LINE_LENGTH+lenght, LINE_WIDTH, _penLine));
                _cursor.setX(_cursor.x() + LINE_LENGTH + SPACE);
                lenght = 0;
            }
        }
    }

    QTimer::singleShot(100, this, SLOT(fitIn()));
}

ActionZone::~ActionZone()
{
    delete _ui;
}

void ActionZone::nextStep(bool succes)
{
    if (_current_step < _ellipseItem.size())
    {
        if (succes)
        {
            _ellipseItem[_current_step]->setPen(_penSuccess);
        }
        else
        {
            _ellipseItem[_current_step]->setPen(_penFail);
        }

        _current_step++;
    }
}

void ActionZone::resetStep()
{
    for (int i=0; i<_ellipseItem.size(); i++)
    {
        _ellipseItem[i]->setPen(_penPoint);
    }

    _current_step=0;
}

void ActionZone::fitIn()
{
    qDebug() << "FIT";
    _ui->graphicsView->fitInView(_scene->sceneRect(),Qt::KeepAspectRatio);
    _ui->graphicsView->scale(0.95,0.95);
    QTimer::singleShot(500, this, SLOT(fitIn()));
}


