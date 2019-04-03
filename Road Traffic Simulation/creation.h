#ifndef CREATION_H
#define CREATION_H
#include "stdlib.h"
#include <vector>
using namespace std;
struct configureSettings{
	char Road_Id[100];
    int Road_Length = 0;
    int Road_Width = 0;
    
    int maxspeed_car = 0;
    int maxspeed_bike = 0;
    int maxspeed_truck = 0;
    int maxspeed_auto = 0;
    
    int acc_bike = 0;
    int acc_car = 0;
    int acc_truck = 0;
    int acc_auto = 0;

    int redlight_pos = 0;
    int timefor_signals[3];
}control;

#endif