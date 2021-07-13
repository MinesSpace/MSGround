#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
};
#endif // MAINWINDOW_H
