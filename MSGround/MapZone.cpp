#include "MapZone.h"
#include "ui_MapZone.h"

#include <QDesktopServices>
#include <QtWebEngine>
#include <QWebEngineView>
#include <QUrl>

MapZone::MapZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapZone)
{
    ui->setupUi(this);

    //auto url_translators = QUrl(QString());

    QWebEngineView *view = new QWebEngineView(parent);
    view->load(QUrl("https://www.openstreetmap.org/#map=10/44.6911/2.6944"));

    ui->map_layout->addWidget(view);
}

MapZone::~MapZone()
{
    delete ui;
}
