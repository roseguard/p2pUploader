<<<<<<< HEAD
#include "widget.h"
#include <QCoreApplication>
#include <QDebug>
#include <QWidget>
#include <QFile>

template <class>
struct ARRAY_SIZE;

template <class T, std::size_t N>
struct ARRAY_SIZE<T[N]>
{
    static constexpr std::size_t SIZE = N;
};

template <class T, std::size_t N1, std::size_t N2>
struct ARRAY_SIZE<T[N1][N2]>
{
    static constexpr std::size_t SIZE = N1 * N2;
};

template <class T, std::size_t N1, std::size_t N2, std::size_t N3>
struct ARRAY_SIZE<T[N1][N2][N3]>
{
    static constexpr std::size_t SIZE = N1 * N2 * N3;
};

template<class T>
constexpr std::size_t get_array_size(const T&)
{
    return ARRAY_SIZE<T>::SIZE;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject e[15][18][13];
    qDebug() << get_array_size(e);

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
=======
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
>>>>>>> d6a68fc62a36db09d520549d288f01e13205569d
