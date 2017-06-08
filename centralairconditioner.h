#ifndef CENTRALAIRCONDITIONER_H
#define CENTRALAIRCONDITIONER_H

#include <QTime>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QList>

#define LOWSPEED 0
#define MEDIUMSPEED 1
#define HIGHSPEED 2



 class centralAirConditioner : public QObject
{
    Q_OBJECT
public:
    centralAirConditioner();
//    centralAirConditioner(QString &user1, QString &roomNum1, float &temperature1, float &workTemperature1, int &blowSpeed1\
//                          , int &degree1, float &cost1, int& workModel1);
        centralAirConditioner(QString user1, QString roomNum1, float temperature1, float workTemperature1, int blowSpeed1\
                              , int degree1, float cost1, int workModel1);
    ~centralAirConditioner();
    float GetTemperature();
    float GetWorkTemperature();
    int GetBlowSpeed();
    float GetCost();
    float GetDegree();
    QString GetUser();
    QString GetRoomNum();
    int GetWorkModel();
    float GetLowTem();
    float GetHighTem();
    void SetRoomNum(const QString &);
    void SetUser(const QString &);
    int ChangeTemperature(int tmp);
    int ChangeBlowSpeed(int tmp);
    void Init();
    QTime time;

public slots:
//    void TimeStart();
//    void TimeStop();

private:
    QString user;
    QString roomNum;
    float temperature;
    float workTemperature;
    int blowSpeed;
    //unsigned long timeCount;
    int degree; //能量总数
    float cost;

    int workModel;
    float lowTem;
    float highTem;
};

class administrator
{
public:
    administrator();
    ~administrator();
    void SetUser(const QString &temp);
    void SetPasswd(const QString &temp);
    QString GetUser();
    QString GetPasswd();

private:
    QString user;
    QString passwd;
};

//extern QMap <int, centralAirConditioner> *airConditioner;
extern QList <centralAirConditioner> *airConditioner;
//extern centralAirConditioner airConditioner;
extern administrator admin;
//extern QVector<centralAirConditioner> airConditioner ;


#endif // CENTRALAIRCONDITIONER_H
