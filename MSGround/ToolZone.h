#ifndef TOOLZONE_H
#define TOOLZONE_H

#include <QWidget>

namespace
{
    constexpr char COMMAND_CHAR = '/';

    Q_GLOBAL_STATIC_WITH_ARGS(const QString, COMMAND_PLOT, ("PLOT"));

    Q_GLOBAL_STATIC_WITH_ARGS(const QString, ANSWER_PLOT, ("Command PLOT found"));

    Q_GLOBAL_STATIC_WITH_ARGS(const QString, COMMAND_NOT_FOUND, ("Command not found"));
}


namespace Ui {
class ToolZone;
}

class ToolZone : public QWidget
{
    Q_OBJECT

public:
    explicit ToolZone(QWidget *parent = nullptr);
    ~ToolZone();

signals:

    void plotCommand(QString command);

private slots:

    void on_send_pb_2_clicked();

private:
    Ui::ToolZone *ui;
};

#endif // TOOLZONE_H
