#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <sqlite3.h>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>

class databaseControl //: public QObject
{
    //Q_OBJECT
public:
    databaseControl();
    ~databaseControl(){}
    bool Connect(const QString &dbname, QSqlDatabase &db);
    void Init();

//signals:
//    void SignalSendDataFromDB(QString user, QString roomNum, float temperature, float workTemperature, \
//                              int blowSpeed, int workModel, int connectionState, float degree, float cost);

private:
    QSqlDatabase user;
    //QSqlDatabase airConditioner;
    //QSqlQuery *queryAdmin;
};

#endif // DATABASECONTROL_H
