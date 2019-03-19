#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <algorithm>
#include <vector>	
#include <thread>
#include <ctime>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;


class vehicle
{
public:
    string type;
    /* typr constitute
    BIKE-<> CAR-<C> BUS-<BB> TRUCK-<TT>
     */
    int length;
    float x1;float x2;float y;
    float v;float a;
    float maxspeed;
    float leflo;float riglo;float inWay;//this are to be updated at time of using
    vehicle(/* args */);
    ~vehicle();
    void setmaxspeed(float data);void acc(float data);
    void updatelen();

    float lentogo(float deltatime);
    void updatespeed(float deltatime);
};

vehicle::vehicle(/* args */)
{
    this->x1=0;this->x2=0;this->y=0;this->v=0;this->a=0;this->leflo=0;this->riglo=0;
    this->maxspeed=0;this->inWay=0;
}

vehicle::~vehicle()
{
}

void vehicle::setmaxspeed(float data){this->maxspeed=data;}
void vehicle::acc(float data){this->a=data;}
void vehicle::updatelen(/* args */)
{
    length = this->type.length();
}

void vehicle::updatespeed(float deltatime)
{
    if(this->v<this->maxspeed)this->v+=this->a*deltatime;
}
float vehicle::lentogo(float deltatime)
{
    float p;
    if(this->v<this->maxspeed)  p = this->v*deltatime - (1.0/2.0)*this->a*(deltatime*deltatime);
    else p = this->v*deltatime;
    return p;
}


vector<vehicle> objs;

#endif