#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QTcpServer>

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
    QTcpServer *tcpServer;
};

#endif // CLIENT_H
