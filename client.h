#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QString>
#include <QDebug>
//#include <QTcpServer>

class client : public QTcpSocket
{
    Q_OBJECT
public:
    client();
    void Init();

signals:
    void NewTcpConnection();

private slots:
    void OnReceiveData();

private:
    QTcpSocket *tcpSocket;
};

#endif // CLIENT_H
