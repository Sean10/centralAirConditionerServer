#include "databasecontrol.h"
#include "centralairconditioner.h"

databaseControl::databaseControl()//:
   // QObject(parent)
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

    Init();
}



void databaseControl::Init()
{
    //query = new QSqlQuery;
    qDebug() << __func__ << "is running.";
    QSqlQuery create;
    create.prepare("create table if not exists user(\
                     user varchar(50) primary key,\
                     passwd varchar(50)\
                    )");
    if(create.exec())
    {
        qDebug() << "Success to create table user.";
    }
    else
    {
        qDebug() << create.lastError();
        qDebug() << "create table user failed.";
    }
    create.finish();

    create.prepare("create table if not exists tableModel(\
                     roomNum varchar(50) primary key,\
                     user varchar(50),\
                     temperature float,\
                     workTemperature float,\
                     blowSpeed int,\
                     workModel int,\
                     connectState int,\
                     degree float,\
                     cost float\
                    )");
    if(create.exec())
    {
        qDebug() << "Success to create tableModel.";
    }
    else
    {
        qDebug() << create.lastError();
        qDebug() << "create table tableModel failed.";
    }
    create.finish();

    create.prepare("create table if not exists Query(roomNUm_queryStartTime varchar(50), \
                                                     roomNum varchar(50),\
                                                     queryStartTime varchar(50), \
                                                     queryEndTime varchar(50), \
                                                     queryStartTemperature float, \
                                                     queryEndTemperature float, \
                                                     energy float)");
    if(create.exec())
    {
        qDebug() << "Success to create Query.";

    }
    else
    {
        qDebug() << create.lastError();
        qDebug() << "create table tableModel failed.";
    }
    create.finish();

    create.prepare("create table if not exists blowSpeed(roomNUm_queryStartTime varchar(50), \
                                                     windStartTime varchar(50), \
                                                     windEndTime varchar(50), \
                                                     blowSpeed int)");
    if(create.exec())
    {
        qDebug() << "Success to create blowSpeed.";
    }
    else
    {
        qDebug() << create.lastError();
        qDebug() << "create table tableModel failed.";
    }
    create.finish();

    QSqlQuery test;
    test.prepare("insert into user (user,passwd) values('admin','123456')");
    if(test.exec())
    {
        qDebug() << test.lastError();
    }
    else
    {
        qDebug() << "insert table failed.";
    }
    test.finish();

    test.prepare("insert into tableModel \
            values('110', '1111111111111', 30.0, 25.0, 1, 0, 0, 20, 50)");
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
    model.setTable("user");
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
