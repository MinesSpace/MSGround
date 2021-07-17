#include "Datasave.h"

#include <QTime>
#include <QFileDialog>

namespace
{
    Q_GLOBAL_STATIC_WITH_ARGS(const QString, DEFAULT_FILENAME, (""));
}

DataSave::DataSave()
{

}

void DataSave::initFile(bool default_path)
{
    QFile file;

    if (default_path)
    {
        //file.setFileName();
    }
    else
    {
        QDate date = QDate::currentDate();
        QString fileName = QFileDialog::getSaveFileName(0, "Save as", date.toString("yyyyMMdd - .csv"),"csv (*.csv)"); // export csv file
        file.setFileName(fileName);
    }

    txtStream = new QTextStream(&file);

    QTime currentTime;
    currentTime = QTime::currentTime();
}
