QT       += core gui network charts serialport
QT       += webengine webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ActionZone.cpp \
    Datasave.cpp \
    MSButton.cpp \
    MapZone.cpp \
    Plot.cpp \
    PlotZone.cpp \
    Serial/serialport.cpp \
    TTGO_serial.cpp \
    TimeZone.cpp \
    #lib/src/QGVCamera.cpp \
    #lib/src/QGVDrawItem.cpp \
    #lib/src/QGVGlobal.cpp \
    #lib/src/QGVImage.cpp \
    #lib/src/QGVItem.cpp \
    #lib/src/QGVLayer.cpp \
    #lib/src/QGVLayerBing.cpp \
    #lib/src/QGVLayerGoogle.cpp \
    #lib/src/QGVLayerOSM.cpp \
    #lib/src/QGVLayerTiles.cpp \
    #lib/src/QGVLayerTilesOnline.cpp \
    #lib/src/QGVMap.cpp \
    #lib/src/QGVMapQGItem.cpp \
    #lib/src/QGVMapQGView.cpp \
    #lib/src/QGVMapRubberBand.cpp \
    #lib/src/QGVProjection.cpp \
    #lib/src/QGVProjectionEPSG3857.cpp \
    #lib/src/QGVWidget.cpp \
    #lib/src/QGVWidgetCompass.cpp \
    #lib/src/QGVWidgetScale.cpp \
    #lib/src/QGVWidgetText.cpp \
    #lib/src/QGVWidgetZoom.cpp \
    ToolZone.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ActionZone.h \
    Datasave.h \
    MSButton.h \
    MapZone.h \
    Plot.h \
    PlotZone.h \
    Serial/serialport.h \
    TTGO_serial.h \
    TimeZone.h \
    #lib/include/QGeoView/QGVCamera.h \
    #lib/include/QGeoView/QGVDrawItem.h \
    #lib/include/QGeoView/QGVGlobal.h \
    #lib/include/QGeoView/QGVImage.h \
    #lib/include/QGeoView/QGVItem.h \
    #lib/include/QGeoView/QGVLayer.h \
    #lib/include/QGeoView/QGVLayerBing.h \
    #lib/include/QGeoView/QGVLayerGoogle.h \
    #lib/include/QGeoView/QGVLayerOSM.h \
    #lib/include/QGeoView/QGVLayerTiles.h \
    #lib/include/QGeoView/QGVLayerTilesOnline.h \
    #lib/include/QGeoView/QGVMap.h \
    #lib/include/QGeoView/QGVMapQGItem.h \
    #lib/include/QGeoView/QGVMapQGView.h \
    #lib/include/QGeoView/QGVMapRubberBand.h \
    #lib/include/QGeoView/QGVProjection.h \
    #lib/include/QGeoView/QGVProjectionEPSG3857.h \
    #lib/include/QGeoView/QGVWidget.h \
    #lib/include/QGeoView/QGVWidgetCompass.h \
    #lib/include/QGeoView/QGVWidgetScale.h \
    #lib/include/QGeoView/QGVWidgetText.h \
    #lib/include/QGeoView/QGVWidgetZoom.h \
    ToolZone.h \
    mainwindow.h

FORMS += \
    ActionZone.ui \
    MSButton.ui \
    MapZone.ui \
    Plot.ui \
    PlotZone.ui \
    TimeZone.ui \
    ToolZone.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#SUBDIRS += \
#    lib/lib.pro

#DISTFILES += \
    #lib/CMakeLists.txt \
    #lib/lib.pri

RESOURCES += \
    Ressource.qrc
