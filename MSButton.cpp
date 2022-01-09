#include "MSButton.h"
#include "ui_MSButton.h"

MSButton::MSButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSButton)
{
    ui->setupUi(this);
}

MSButton::~MSButton()
{
    delete ui;
}
