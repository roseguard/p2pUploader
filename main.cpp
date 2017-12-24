#include "widget.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(QCoreApplication::arguments().length()<2)
    {
        qDebug() << "Need argument (path to the uploading file)";
        qDebug() << "";
        qDebug() << "If you run it from desktop drag and drop file for uploading on the icon of this programm in system (not here, this one you may close)";
        qDebug() << "";
        qDebug() << "If you running programm from console - put path to the uploading file as argument";
        return a.exec();
    }
    qDebug() << "Selected : " << QCoreApplication::arguments().at(1);
    QFile file(QCoreApplication::arguments().at(1));
    if(!file.exists())
    {
        qDebug() << "File not exists";
        return a.exec();
    }
    qDebug() << "Starting server";
    Server w(QCoreApplication::arguments().at(1));

    return a.exec();
}
