#ifndef MAPZONE_H
#define MAPZONE_H

#include <QWidget>

namespace Ui {
class MapZone;
}

class MapZone : public QWidget
{
    Q_OBJECT

public:
    explicit MapZone(QWidget *parent = nullptr);
    ~MapZone();

private:
    Ui::MapZone *ui;
};

#endif // MAPZONE_H
