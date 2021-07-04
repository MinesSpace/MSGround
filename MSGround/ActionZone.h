#ifndef ACTIONZONE_H
#define ACTIONZONE_H

#include <QWidget>

namespace Ui {
class ActionZone;
}

class ActionZone : public QWidget
{
    Q_OBJECT

public:
    explicit ActionZone(QWidget *parent = nullptr);
    ~ActionZone();

private:
    Ui::ActionZone *ui;
};

#endif // ACTIONZONE_H
