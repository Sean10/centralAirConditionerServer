#ifndef CENTRALAIRCONDITIONER_H
#define CENTRALAIRCONDITIONER_H

#include <QTime>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QVector>

#define LOWSPEED 0
#define MEDIUMSPEED 1
#define HIGHSPEED 2



 class centralAirConditioner : public QObject
{
    Q_OBJECT
public:
    centralAirConditioner();
    ~centralAirConditioner();
    int GetTemperature();
    int GetBlowSpeed();
    double GetCost();
    double GetDegree();
    int ChangeTemperature(int tmp);
    int ChangeBlowSpeed(int tmp);
    void Init();
    QTime time;

public slots:
    void TimeStart();
    void TimeStop();

private:
    QString user;
    int temperature;
    int blowSpeed;
    unsigned long timeCount;
    double degree;
    double cost;
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

extern centralAirConditioner airConditioner;
extern administrator admin;
//extern QVector<centralAirConditioner> airConditioner ;


#endif // CENTRALAIRCONDITIONER_H
