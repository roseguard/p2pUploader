#include "widget.h"
#include <QFileInfo>

#define port 51034

Server::Server(QString fileName, QObject *parent)
    : QObject(parent)
{
    fileString = fileName;
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(getConnected()));
    if(!server->listen(QHostAddress::Any, port))
    {
        qDebug() << "Cannot start server. Maybe port " + QByteArray::number(port) + " is already in work. Check, maybe other program use this port";
        deleteLater();
    }
    qDebug() << "Server started";
}

Server::~Server()
{

}

void Server::getConnected()
{
    socket = server->nextPendingConnection();
    qDebug() << "New connection" << socket->peerAddress();
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    QFile file(fileString);
    file.open(QIODevice::ReadOnly);
    file.size();
    socket->write("HTTP/1.0 200 Ok\r\n");
    socket->write("Content-Disposition: attachment; filename=" + QFileInfo(file).fileName().toUtf8() + "\r\n");
    socket->write("Content-Type: application/xml\r\n");
    socket->write("Connection: Keep-Alive\r\n");
    socket->write("Content-Length: +" + QByteArray::number(file.size()) + "\r\n");
    socket->write("\r\n");
    socket->flush();
    socket->waitForBytesWritten();
    for(int i = 0; i < file.size(); i+=1024)
    {
        if(socket->state()==QTcpSocket::UnconnectedState)
            return;
        if(i%1024000 == 0)
        {
            qDebug() << "Sended : " << i << "/" << file.size();
        }
        socket->write(file.read(1024), 1024);
        socket->flush();
        socket->waitForBytesWritten();
    }
    socket->flush();
}
