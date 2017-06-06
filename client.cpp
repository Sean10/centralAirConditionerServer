#include "client.h"

client::client()
{
    Init();
}

void client::Init()
{
    tcpSocket = new QTcpSocket;
    NewTcpConnection();

    connect(tcpSocket, SIGNAL(readyRead()), SLOT(OnReceiveData()));
}

void client::NewTcpConnection()
{
    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1", 6666);
}

void client::OnReceiveData()
{
    QString data = tcpSocket->readAll();
    qDebug() << data;
}
