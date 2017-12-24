#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QFile>

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QString fileName, QObject *parent = 0);
    ~Server();
public slots:
    void getConnected();
private:
    QTcpServer *server;
    QTcpSocket *socket;

    QString fileString;
};

#endif // WIDGET_H
