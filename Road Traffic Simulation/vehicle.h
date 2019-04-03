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
    BIKE-<B> CAR-<C> AUTO-<AA> TRUCK-<TTT>
     */
    int length;
    int x1;int x2;int y;
    int v;int a;
    int maxspeed;
    int leflo;int riglo;int inWay;
    bool lefspace=true;bool rigspace=true;//this are to be updated at time of using
    bool rotright; bool rotleft;
    vehicle(/* args */);
    ~vehicle();
    void updatelen();

    int lentogo(int deltatime);
    void updatespeed(int deltatime);
};

vehicle::vehicle(/* args */)
{
    this->x1=0;this->x2=0;this->y=0;this->v=0;this->a=0;this->leflo=0;this->riglo=0;
    this->maxspeed=0;this->inWay=0;this->rotleft=false;this->rotright=false;
}

vehicle::~vehicle()
{
}


void vehicle::updatelen(/* args */)
{
    length = this->type.length();
}

void vehicle::updatespeed(int deltatime)
{
    if(this->v<this->maxspeed)this->v+=this->a*deltatime;
}
int vehicle::lentogo(int deltatime)
{
    int p;
    p = this->v*deltatime;
    return p;
}


vector<vehicle> objs;



#endif