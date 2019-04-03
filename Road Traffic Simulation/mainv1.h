#ifndef MAINV1_H
#define MAINV1_H
#include "stdlib.h"
#include <cstdlib>
#include "unistd.h"
#include <algorithm>
#include <vector>	
#include <thread>
#include <ctime>
#include <random>
#include <chrono>
#include <cmath>
#include "vehicle.h"
#include "changemap.h"
#include "creation.h"
#define Vector_Matrix_Float vector<vector<char>>
using namespace std;

void print(Vector_Matrix_Float v){
    for(int i=0;i<v.size();i++){
      for(int j=0;j<v[0].size();j++){
          cout<<v[i][j]<<" ";  
      }
      cout<<endl;
  }
}


// Returns a boundry frame of simulation
Vector_Matrix_Float getBoundry(int width,int length){
	Vector_Matrix_Float b(width,vector<char>(length,' '));
	for(int i=0;i<b.size();i++){
		for(int j=0;j<b[0].size();j++){
			if(i*j==0 || (b.size()-1-i)*(b[0].size()-1-j)==0){
				b[i][j]='-';
			} else {
				b[i][j] = ' ';
			}
		}
	}
	return b;
}
Vector_Matrix_Float enableRedLight(Vector_Matrix_Float lousy){
	Vector_Matrix_Float boundry = lousy;
	for(int i=1;i<boundry.size()-1;i++){
		boundry[i][control.redlight_pos] = '|'; // Change its colour to RED
	}
	return boundry;
}

Vector_Matrix_Float disableRedLight(Vector_Matrix_Float lousy){
	Vector_Matrix_Float boundry = lousy;
	for(int i=1;i<boundry.size()-1;i++){
		if(boundry[i][control.redlight_pos]!='B')boundry[i][control.redlight_pos] = ' ';
	}
	return boundry;
}

#endif