#include "ToolZone.h"
#include "ui_ToolZone.h"

ToolZone::ToolZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolZone)
{
    ui->setupUi(this);
}

ToolZone::~ToolZone()
{
    delete ui;
}

void ToolZone::on_send_pb_2_clicked()
{
    QString command = ui->command_lbl->text();
    QString answer;

    if (command.at(0) == COMMAND_CHAR)
    {
        if (command.contains(COMMAND_PLOT->toUtf8()))
        {
            answer =  ANSWER_PLOT->toUtf8();
            emit plotCommand(command);
        }
        else
        {
            answer = COMMAND_NOT_FOUND->toUtf8();
        }

    }

    ui->console->setPlainText(ui->console->toPlainText() + "\n" + command + " \n" + answer);
}
