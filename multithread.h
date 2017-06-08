#ifndef MULTITHREAD_H
#define MULTITHREAD_H

#include <QThread>
#include <QSqlDatabase>
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QTcpSocket>
#include <QTimer>
#include <QSqlQuery>

class multithread: public QThread
{
    Q_OBJECT
public:
    multithread(qintptr s, int state, QObject *parent);
    ~multithread();
    void run() Q_DECL_OVERRIDE;
    void UpdateCentralAirConditioner();

private slots:
    void DealWithMessage();
    void SendConsumptionMessage();
    void SendRequireMessage();
    void UpdateEnergy();

private:
    qintptr socketDescriptor;

    int workModel;
    int connectState;
    int degree;

    QString roomNum;
    QString user;
    float temperature;
    int blowSpeed;

    int queryStart;
    QString queryStartTime;
    QString queryEndTime;
    QString windStartTime;
    QString windEndTime;
    float queryStartTemperature;
    float queryEndTemperature;
    float queryStartEnergy;
    float queryEndEnergy;

    QSqlDatabase database;
    QString dblink;

    QTcpSocket *tcpSocket;
};

#endif // MULTITHREAD_H
