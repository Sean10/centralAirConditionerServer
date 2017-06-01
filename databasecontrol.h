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

class databaseControl
{
public:
    databaseControl();
    bool Connect(const QString &dbname, QSqlDatabase &db);
    void Init();

private:
    QSqlDatabase user;
    //QSqlDatabase airConditioner;
    QSqlQuery *queryAdmin;
};

#endif // DATABASECONTROL_H
