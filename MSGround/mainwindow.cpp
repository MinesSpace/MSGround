#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->ToolZone_wdg, &ToolZone::plotCommand, ui->PlotZone_wdg->plot(), &Plot::newCommand);

    ui->PlotZone_wdg->plot()->addLinePlot("test");
    ui->PlotZone_wdg->plot()->appendData(0, QPointF(0, 0));
    ui->PlotZone_wdg->plot()->appendData(0, QPointF(1, 2));

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
