#include "widget.h"
#include <QFileInfo>
#include <QNetworkInterface>
#define port 51034

Server::Server(QString fileName, QObject *parent)
    : QObject(parent)
{
    fileString = fileName;
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(getConnected()));
    int changePort = 0;
    while(!server->listen(QHostAddress::Any, port+changePort))
    {
        qDebug() << "\nCannot start server on port " + QByteArray::number(port+changePort);
        qDebug() << "Trying to start server on " << port+(++changePort);
    }
    qDebug() << "\nServer started on port : " << server->serverPort();
    qDebug() << "\nNow you can use your address and port to download " << fileString << " from network";
    qDebug() << "\nExample for localhost(only for your computer) 127.0.0.1:" << server->serverPort();
    qDebug() << "\nExample for some example local network(only for computer in your local network) 192.168.0.201:" << server->serverPort();
    qDebug() << "\nLast one was only example address. If you want to send file in internet find out your public address. If you do not know how, you may try to find out on 2ip.ru";

    qDebug() << "\nAlso you may found your public or local address in this list (it may work only in some cases)";
    auto list = QNetworkInterface::allAddresses();
    for(int i = 0; i < list.length(); i++)
    {
        qDebug() << list.at(i).toString();
    }

    qDebug() << "";
    qDebug() << "(c) roseguardd@gmail.com";
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
