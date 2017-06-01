#include "centralairconditioner.h"

centralAirConditioner::centralAirConditioner()
{
    Init();

}

centralAirConditioner::~centralAirConditioner()
{
    delete this;
}

void centralAirConditioner::Init()
{
    temperature = 25;
    blowSpeed = LOWSPEED;
    degree = 0;
    cost = 0;
    timeCount = 0;
}

int centralAirConditioner::GetBlowSpeed()
{
    return this->blowSpeed;
}

int centralAirConditioner::GetTemperature()
{
    return this->temperature;
}

double centralAirConditioner::GetCost()
{
    return this->cost;
}

double centralAirConditioner::GetDegree()
{
    return this->degree;
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

void centralAirConditioner::TimeStart()
{
    time.start();
}

void centralAirConditioner::TimeStop()
{
    int time_diff = time.elapsed()/100;
    switch(blowSpeed)
    {
        case 0:
            degree += time_diff;
            cost += time_diff * 0.01;
            break ;
        case 1:
            degree += time_diff*2;
            cost += time_diff * 0.02;
            break;
        case 2:
            degree += time_diff*3;
            cost += time_diff * 0.03;
            break;
        default:
            qDebug() << "Error: blowspeed is wrong." << endl;
    }

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
