#include "ActionZone.h"
#include "ui_ActionZone.h"

ActionZone::ActionZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionZone)
{
    ui->setupUi(this);
}

ActionZone::~ActionZone()
{
    delete ui;
}
