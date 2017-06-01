#include "databasecontrol.h"
#include "centralairconditioner.h"

databaseControl::databaseControl()
{
    //qDebug() << QSqlDatabase::drivers();
    QFile testFile("user.db");
   if (testFile.exists())
       qDebug() << "user.db exists";
   else
       qDebug() << "user.db doesn't exist.";

    //路径这里存在问题，为什么添加了qrc之后依旧不需要前缀就可以使用了呢？
    if(Connect("user.db",user))
    {
        qDebug() << "Database user Create Successfully!";
    }
    else
    {
        qDebug() << "Database user Create Failed!";
    }

//    if(Connect("airConditioner.db", airConditioner)){
//        qDebug() << "Database airConditioner Create Successfully!";
//    }
//    else{
//        qDebug() << "Database airConditioner Create Failed!";
//    }
    Init();
}

void databaseControl::Init()
{
    //query = new QSqlQuery;
    qDebug() << __func__ << "is running.";
    QSqlQuery create;
    create.prepare("create table if not exists data(\
                     user varchar(50) primary key,\
                     passwd varchar(50)\
                    )");
    if(create.exec())
    {
        qDebug() << create.lastError();
    }
    else
    {
        qDebug() << "create table failed.";
    }
    create.finish();

    QSqlQuery test;
    test.prepare("insert into data (user,passwd) values('admin','123456')");
    if(test.exec())
    {
        qDebug() << test.lastError();
    }
    else
    {
        qDebug() << "insert table failed.";
    }
    test.finish();

    QSqlTableModel model;
    model.setTable("data");
    if(model.select())
    {
        QSqlRecord record = model.record(0);
        QString name = record.value("user").toString();
        QString passwd = record.value("passwd").toString();
        admin.SetUser(name);
        admin.SetPasswd(passwd);
        qDebug() << name << passwd;
    }
//    queryAdmin = new QSqlQuery;
//    queryAdmin->exec("select * from data");
//    while(queryAdmin->next())
//    {
//        //qDebug() << queryAdmin->;
//        admin.SetUser(queryAdmin->value(0).toString());
//        admin.SetPasswd(queryAdmin->value(1).toString());
//        qDebug() << queryAdmin->value(0).toString();
//        qDebug() << queryAdmin->value(1).toString();
//    }
//    qDebug() << admin.GetUser() << admin.GetPasswd();
}

bool databaseControl::Connect(const QString &dbName, QSqlDatabase &db)
{
    qDebug() << __func__ << "is running.";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if(!db.open())
    {
        QMessageBox::warning(0, QObject::tr("Database Error"),
        db.lastError().text());
        qDebug() << "Database open error!";
        return false;
    }
    else
    {
        return true;
    }
}
