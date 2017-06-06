#include "server.h"
#include "multithread.h"

server::server(QObject *parent):
    QTcpServer (parent)
{
    state = 0;
}

void server::incomingConnection(qintptr socketDescriptor)
{
    multithread *thread = new multithread(socketDescriptor, state, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
