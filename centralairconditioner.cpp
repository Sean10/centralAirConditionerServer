#include "centralairconditioner.h"

centralAirConditioner::centralAirConditioner()
{
    Init();

}

centralAirConditioner::centralAirConditioner(QString user1, QString roomNum1, float temperature1, float workTemperature1, int blowSpeed1\
                      , int degree1, float cost1, int workModel1)
{
    user = user1;
    roomNum = roomNum1;
    temperature = temperature1;
    workTemperature = workTemperature1;
    //工作温度可能需要修改；
    blowSpeed = blowSpeed1;
    degree = degree1;
    cost = cost1;
    workModel = workModel1;
}

centralAirConditioner::~centralAirConditioner()
{
    delete this;
}

void centralAirConditioner::Init()
{
    user = "";
    roomNum = "";
    temperature = 25;
    blowSpeed = LOWSPEED;
    degree = 0;
    cost = 0;
    //timeCount = 0;
}
int centralAirConditioner::GetBlowSpeed()
{
    return this->blowSpeed;
}

float centralAirConditioner::GetTemperature()
{
    return this->temperature;
}

float centralAirConditioner::GetWorkTemperature()
{
    return this->workTemperature;
}

float centralAirConditioner::GetCost()
{
    return this->cost;
}

float centralAirConditioner::GetDegree()
{
    return this->degree;
}

QString centralAirConditioner::GetUser()
{
    return this->user;
}

QString centralAirConditioner::GetRoomNum()
{
    return this->roomNum;
}

int centralAirConditioner::GetWorkModel()
{
    return this->workModel;
}

float centralAirConditioner::GetLowTem()
{
    return this->lowTem;
}

float centralAirConditioner::GetHighTem()
{
    return this->highTem;
}

void centralAirConditioner::SetUser(const QString &user)
{
    this->user = user;
}

void centralAirConditioner::SetRoomNum(const QString &roomNum)
{
    this->roomNum = roomNum;
}

int centralAirConditioner::ChangeTemperature(int tmp)
{
    this->temperature = tmp;
    return 0;
}

int centralAirConditioner::ChangeBlowSpeed(int tmp)
{
    this->blowSpeed = tmp;
    return 0;
}

administrator::administrator()
{

}

administrator::~administrator()
{

}

void administrator::SetPasswd(const QString &temp)
{
    this->passwd = temp;
}

void administrator::SetUser(const QString &temp)
{
    this->user = temp;
}

QString administrator::GetUser()
{
    return this->user;
}

QString administrator::GetPasswd()
{
    return this->passwd;
}
