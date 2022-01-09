#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
//#include "Serial/serialport.h"
#include <TTGO_serial.h>
#include "datasave.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots :
    void refreshData();

private slots:
    void on_actionStart_chrono_triggered();

    void on_actionStop_chrono_triggered();

    void on_actionReset_chrono_triggered();

    void on_actionGo_to_Australia_triggered();

    void on_actionGo_to_troducdumonde_triggered();

    void on_actionGo_to_plusBelleVilleDuMonde_triggered();

    void on_actionNext_Succes_triggered();

    void on_actionNext_Fail_triggered();

    void on_actionReset_triggered();



private:
    Ui::MainWindow *ui;
    TTGO_serial *_serial;

    DataSave *datasave;

    QTimer _timer_data;
    void connected();
    void error(QString errorString);

    long _max_altitude=0;
    int _etat_seq=0;

    int compteur = 0;

};
#endif // MAINWINDOW_H
