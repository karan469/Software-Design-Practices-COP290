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
using namespace std;

#define Vector_Matrix_Float vector<vector<char>>


Vector_Matrix_Float changeMap(Vector_Matrix_Float lousy,bool red){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));
	string allVehicles[] = {"<>", "<C>", "<BB>", "<TT>"};

	Vector_Matrix_Float boundry = lousy;
	
	// Increment every vehicle in each frame
	boundry = incrementVehicle(boundry,red);

	// Introduce a new vehicle with (probably) probability of 15%
	for(int k=1;k<boundry.size()-1;k++){
		if(boundry[k][1]==' ')
		{
			// cout << "gone"<<endl;
			if(boundry[k][1]==' ' && rand()/rand_max<0.07){	
				int c = (int)floor((rand()/rand_max)*4);
				vehicle p = vehicle();
				p.type = allVehicles[c];
				p.y = k;
				p.v = 1.0;
				if (c==0) {
					p.setmaxspeed(2.0);
					p.acc(1.0);
				}
				else if (c==1)
				{
					p.setmaxspeed(2.0);
					p.acc(1.0);
				}
				else if (c==2)
				{
					p.setmaxspeed(1.0);
					p.acc(1.0);
				}
				else if (c==3)
				{
					p.setmaxspeed(1.0);
					p.acc(1.0);
				}
				p.updatelen();
				objs.push_back(p);
			}
		}
	}
	return boundry;
}

#endif