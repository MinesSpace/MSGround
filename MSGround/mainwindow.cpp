#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->ToolZone_wdg, &ToolZone::plotCommand, ui->PlotZone_wdg->plot1(), &Plot::newCommand);

    ui->PlotZone_wdg->plot1()->enableCurve(SPEED);
    ui->PlotZone_wdg->plot1()->enableCurve(ALTITUDE);

    ui->PlotZone_wdg->plot2()->enableCurve(ACCELERO_X);
    ui->PlotZone_wdg->plot2()->enableCurve(ACCELERO_Y);
    ui->PlotZone_wdg->plot2()->enableCurve(ACCELERO_Z);

    //ui->PlotZone_wdg->plot()->addLinePlot("test");
    //ui->PlotZone_wdg->plot()->appendData(0, QPointF(0, 0));
    //ui->PlotZone_wdg->plot()->appendData(0, QPointF(1, 2));

    //QString link = "https://www.google.fr/maps/@48.8556087,2.3324398,737m/data=!3m1!1e3";
    //QDesktopServices::openUrl(QUrl(link));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionStart_chrono_triggered()
{
    ui->TimeZone_wdg->startChrono();
}

void MainWindow::on_actionStop_chrono_triggered()
{
    ui->TimeZone_wdg->stopChrono();
}

void MainWindow::on_actionReset_chrono_triggered()
{
    ui->TimeZone_wdg->resetChrono();
}

void MainWindow::on_actionGo_to_Australia_triggered()
{
    ui->MapZone_wdg->setPosition(-27.6835, 128.0649);
}

void MainWindow::on_actionGo_to_troducdumonde_triggered()
{
    ui->MapZone_wdg->setPosition(43.2184361, -0.047333333);
}

void MainWindow::on_actionGo_to_plusBelleVilleDuMonde_triggered()
{
    ui->MapZone_wdg->setPosition(43.601846, 1.465393);
}

void MainWindow::on_actionNext_Succes_triggered()
{
    ui->ActionZone_wdg->nextStep(true);
}

void MainWindow::on_actionNext_Fail_triggered()
{
    ui->ActionZone_wdg->nextStep(false);
}

void MainWindow::on_actionReset_triggered()
{
    ui->ActionZone_wdg->resetStep();
}
