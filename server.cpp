#include "server.h"

server::server(QObject *parent):
    QTcpServer (parent)
{

}

void server::incomingConnection(qintptr socketdescriptor)
{

}
