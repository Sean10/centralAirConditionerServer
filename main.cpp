#include "mainwindow.h"
#include <QApplication>
#include "centralairconditioner.h"
#include "databasecontrol.h"

//QVector<centralAirConditioner> airConditioner ;
centralAirConditioner airConditioner;
administrator admin;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    databaseControl database;
    MainWindow *w = new MainWindow;


    QObject::connect(w,SIGNAL(TimeStartSignal()),&airConditioner, SLOT(TimeStart()));
    QObject::connect(w,SIGNAL(TimeStopSignal()),&airConditioner,SLOT(TimeStop()));

    //w->show();

    return a.exec();
}
