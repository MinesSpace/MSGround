#include "MapZone.h"
#include "ui_MapZone.h"
MapZone::MapZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapZone)
{
    ui->setupUi(this);

    //auto url_translators = QUrl(QString())


    view = new QWebEngineView(parent);
    view->load(QUrl("https://www.openstreetmap.org/?&mlat=48.85669&mlon=2.35147#map=17/48.85669/2.35147"));


    ui->map_layout->addWidget(view);
}

MapZone::~MapZone()
{
    delete ui;
}

void MapZone::setPosition(double x, double y)
{
    QString url;
    url = URL_PREFIX->toUtf8() + "?&mlat=" + QString::number(x) +
          "&mlon=" + QString::number(y) +
          "#map=" + QString::number(DEFAULT_ZOOM) + "/" + QString::number(x) + "/" + QString::number(y);

    view->load(QUrl(url));
}
