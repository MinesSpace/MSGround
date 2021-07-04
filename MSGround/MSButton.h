#ifndef MSBUTTON_H
#define MSBUTTON_H

#include <QWidget>

namespace Ui {
class MSButton;
}

class MSButton : public QWidget
{
    Q_OBJECT

public:
    explicit MSButton(QWidget *parent = nullptr);
    ~MSButton();

private:
    Ui::MSButton *ui;
};

#endif // MSBUTTON_H
