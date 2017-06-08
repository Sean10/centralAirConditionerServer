#include "mainwindow.h"
#include <QApplication>
#include "centralairconditioner.h"
#include "databasecontrol.h"
#include "server.h"
#include "multithread.h"

//QMap <int, centralAirConditioner> *airConditioner;
QList <centralAirConditioner> *airConditioner;
//centralAirConditioner airConditioner;
administrator admin;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    databaseControl database;
    MainWindow *w = new MainWindow;


//    QObject::connect(&database, SIGNAL(SignalSendDataFromDB(QString user, QString roomNum, float temperature, float workTemperature, \
//                                                            int blowSpeed, int workModel, int connectionState, float degree, float cost)),\
//                     w, SLOT(RevDateFromDB(QString user, QString roomNum, float temperature, float workTemperature, \
//                                           int blowSpeed, int workModel, int connectionState, float degree, float cost)));
    //QObject::connect(w,SIGNAL(TimeStartSignal()),&airConditioner, SLOT(TimeStart()));
    //QObject::connect(w,SIGNAL(TimeStopSignal()),&airConditioner,SLOT(TimeStop()));

//    tcpServer = new QTcpServer(this);
//    if(!tcpServer->listen(QHostAddress::Any, 6666))
//    {
//        qDebug() << tcpServer->errorString();
//    }

//    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(AcceptConnection()));


    //w->show();
    server *servers;
    servers = new server;
    servers->listen(QHostAddress::Any,6666);

    return a.exec();
}
