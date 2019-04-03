#ifndef CHANGEMAP_H
#define CHANGEMAP_H
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>	
#include <thread>
#include <ctime>
#include <random>
#include <chrono>
#include <cmath>
#include "vehicle.h"
#include "incrementVehicle.h"
#include "creation.h"
using namespace std;

#define Vector_Matrix_Float vector<vector<char>>

bool initial = true;
int p = 0;
Vector_Matrix_Float changeMap(Vector_Matrix_Float lousy,bool red){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));
	string allVehicles[] = {"CC", "B", "TTT", "AA"};

	Vector_Matrix_Float boundry = lousy;

	// Increment every vehicle in each frame
	boundry = incrementVehicle(boundry,red);

	// Introduce a new vehicle with (probably) probability of maximum 8%
	for(int k=1;k<boundry.size()-1;k++){
		int c = (int)floor((rand()/rand_max)*4);
		if(boundry[k][1]==' ' && rand()/rand_max<0.08 )
		{
			vehicle p = vehicle();
			p.type = allVehicles[c];
			p.y = k;
			p.v = 1.0;
			if (c==0)
			{
				p.maxspeed = control.maxspeed_bike;
				p.a = control.acc_bike;			
			}
			else if (c==1)
			{
				p.maxspeed = control.maxspeed_car;
				p.a = control.acc_car;
			}
			else if (c==2 && rand()/RAND_MAX<0.65)
			{
				p.maxspeed = control.maxspeed_truck;
				p.a = control.acc_truck;
			}
			else if (c==3 && rand()/RAND_MAX<0.7)
			{
				p.maxspeed = control.maxspeed_auto;
				p.a = control.acc_auto;
			}
			p.updatelen();
			objs.push_back(p);
			
		}
	}
	return boundry;
}

#endif