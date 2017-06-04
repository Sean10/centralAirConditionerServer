#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QDebug>
//#include <QStringList>
#include <QObject>
#include <QString>
//#include <QTcpServer>

class server : public QTcpServer
{
    Q_OBJECT
public:
    server(QObject *parent = 0);

private slots:
    void incomingConnection(qintptr socketdescriptor) Q_DECL_OVERRIDE;

private:
    QString receive;
    QString sender;
    int state;
};

#endif // SERVER_H
