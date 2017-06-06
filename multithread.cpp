#include "multithread.h"

multithread::multithread(qintptr s, int state, QObject *parent):
    QThread(parent),socketDescriptor(s)
{
    workState = state;
    connectState = 1;
    energy = 0;
    blowSpeed = -1;// 我设定的是0、1、2，他们的协议里似乎设定的是-1、0、1？

    queryStart = 0;
    QDateTime time = QDateTime::currentDateTime();
    dblink=time.toString("hh:mm:ss");

    database=QSqlDatabase::addDatabase("QSQLITE",dblink);
    database.setDatabaseName("user.db");
    if(database.open())
    {
        qDebug()<<"database opened";
    }
    else
    {
        qDebug()<<"database open failed";
    }
}

multithread::~multithread()
{
    qDebug()<<"thread terminated.";
}

void multithread::run()
{
    QTimer timer1;
    QTimer timer2;
    QTimer timer3;
    tcpSocket=new QTcpSocket;
    if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
        qDebug()<<"error";
        return;
    }
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(DealWithMessage()),Qt::DirectConnection);
    connect(&timer1,SIGNAL(timeout()),this,SLOT(SendConsumptionMessage()),Qt::DirectConnection);
    connect(&timer2,SIGNAL(timeout()),this,SLOT(SendRequireMessage()),Qt::DirectConnection);
    connect(&timer3,SIGNAL(timeout()),this,SLOT(UpdateEnergy()),Qt::DirectConnection);
    timer1.start(4000);
    timer2.start(2000);
    timer3.start(1000);
    this->exec();
    qDebug()<<1;
    while(connectState!=0)
    {
    }
    timer1.stop();
    timer2.stop();
    timer3.stop();
    tcpSocket->disconnectFromHost();
    tcpSocket->waitForDisconnected();
    //this->exec();
}

void multithread::DealWithMessage()
{
    QString data=tcpSocket->readAll();
    int count=0;
    QString id="";
    QString out;
    QString wind;
    QString temp;
    QByteArray sendMessage;
    QDateTime time;
    QSqlQuery query(QSqlDatabase::database(dblink));

    qDebug()<<data;
    if(data[0]=='c')
    {
        roomNum="";
        while(data[count]!='/')
        {
            count=count+1;
        }
        count=count+1;
        while(data[count]!='/')
        {
            roomNum=roomNum+data[count];
            count=count+1;
        }
        count=count+1;
        while(count<data.length())
        {
            id=id+data[count];
            count=count+1;
        }
        if(1)//检查id
        {
            if(workState==0)
            {
                out="serverMsg/0/18/25";
            }
            else
            {
                out="serverMsg/1/25/30";
            }
            sendMessage = out.toLocal8Bit();
            tcpSocket->write(sendMessage);
        }
        else
        {
            connectState=0;
        }
    }
    else if(data=="request")
    {
        out="answer";
        sendMessage=out.toLocal8Bit();
        tcpSocket->write(sendMessage);
        if(queryStart==0)
        {
            time=QDateTime::currentDateTime();
            queryStartTime=time.toString("yyyy-MM-dd hh:mm:ss ddd");
            queryStartTemperature = temperature;
            queryStartEnergy=energy;
            windStartTime=time.toString("yyyy-MM-dd hh:mm:ss ddd");
            queryStart=1;
        }
    }
    else if(data[0]=='w')
    {
        out="acceptWind";
        sendMessage=out.toLocal8Bit();
        tcpSocket->write(sendMessage);
        while(data[count]!='/')
        {
            count=count+1;
        }
        count=count+1;
        wind=data[count];
        if(queryStart==0)
        {
            blowSpeed=wind.toInt();
            time=QDateTime::currentDateTime();
            queryStartTime=time.toString("yyyy-MM-dd hh:mm:ss ddd");
            queryStartTemperature=temperature;
            queryStartEnergy=energy;
            windStartTime=time.toString("yyyy-MM-dd hh:mm:ss ddd");
            queryStart=1;
        }
        else
        {
            time=QDateTime::currentDateTime();
            windEndTime=time.toString("yyyy-MM-dd hh:mm:ss ddd");
            //这里为插入风速数据库操作
            query.prepare("insert into Windspeed values(?,?,?,?)");
            query.addBindValue(roomNum+queryStartTime);
            query.addBindValue(windStartTime);
            query.addBindValue(windEndTime);
            query.addBindValue(blowSpeed);
            query.exec();
            query.finish();
            windStartTime=time.toString("yyyy-MM-dd hh:mm:ss ddd");
            blowSpeed=wind.toInt();
        }

    }
    else if(data=="requestEnd")
    {
        //connectstate=0;
        time=QDateTime::currentDateTime();
        queryEndTime=time.toString("yyyy-MM-dd hh:mm:ss ddd");
        queryEndTemperature=temperature;
        queryEndEnergy=energy;
        windEndTime=time.toString("yyyy-MM-dd hh:mm:ss ddd");
        //这里为插入请求数据库和风速数据库操作
        query.prepare("insert into Query values(?,?,?,?,?,?,?)");
        query.addBindValue(roomNum+queryStartTime);
        query.addBindValue(roomNum);
        query.addBindValue(queryStartTime);
        query.addBindValue(queryEndTime);
        query.addBindValue(queryStartTemperature);
        query.addBindValue(queryEndTemperature);
        query.addBindValue((queryEndEnergy-queryStartEnergy)*5);
        query.exec();
        query.finish();
        query.prepare("insert into Windspeed values(?,?,?,?)");
        query.addBindValue(roomNum+queryStartTime);
        query.addBindValue(windStartTime);
        query.addBindValue(windEndTime);
        query.addBindValue(blowSpeed);
        query.exec();
        query.finish();
        queryStart=0;
    }
    else if(data[0]=='a')
    {
        while(data[count]!='/')
        {
            count=count+1;
        }
        count=count+1;
        while(data[count]!='/')
        {
            temp=temp+data[count];
            count=count+1;
        }
        count=count+1;
        while(data[count]!='/')
        {
            count=count+1;
        }
        count=count+1;
        wind=data[count];
        temperature=temp.toFloat();
        blowSpeed=wind.toInt();
    }
    else
    {
    }
}

void multithread::SendConsumptionMessage()
{
    QString out;
    QByteArray sendMessage;
    out="cost/"+QString::number(energy)+'/'+QString::number(energy*5);
    sendMessage = out.toLocal8Bit();
    tcpSocket->write(sendMessage);
}

void multithread::SendRequireMessage()
{
    QString out;
    QByteArray sendMessage;
    out="request";
    sendMessage = out.toLocal8Bit();
    tcpSocket->write(sendMessage);
}

void multithread::UpdateEnergy()
{
    if(blowSpeed==0&&queryStart==1)
    {
        energy=energy+0.8;
    }
    else if(blowSpeed==1&&queryStart==1)
    {
        energy=energy+1;
    }
    else if(blowSpeed==2&&queryStart==1)
    {
        energy=energy+1.3;
    }
    else
    {
    }
}

