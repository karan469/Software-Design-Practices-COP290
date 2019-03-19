#include "stdlib.h"
#include <cstdlib>
#include <iostream>
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
Vector_Matrix_Float getBoundry(){
	Vector_Matrix_Float b(10,vector<char>(30,' '));
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
		boundry[i][15] = '|'; // Change its colour to RED
	}
	return boundry;
}

Vector_Matrix_Float disableRedLight(Vector_Matrix_Float lousy){
	Vector_Matrix_Float boundry = lousy;
	for(int i=1;i<boundry.size()-1;i++){
		boundry[i][15] = ' ';
	}
	return boundry;
}
// this version moves only one vehicle --> ideal function version 2.0
void translate(Vector_Matrix_Float boundry, int a, int b){
	int k = 0;
	if(a*b==0 || (boundry.size()-1-a)*(boundry[0].size()-1-b)==0){
		// leave it empty
	} else {
		// boundry[a][k] = '';
		// vehicle d = vehicle();
		// d.y=1;
		// d.type="<BB>";
		// d.updatelen();
		// d.maxspeed = 1.0;
		// d.v=1.0;
		// d.a=.1;

		// objs.push_back(d);

		cout<<"Time frame: "<<k<<endl;
		
		print(boundry);
		printf("\033c");
        k=k+1;
		while(k<=8){
			usleep(180000);
			cout<<"\b";
			cout<<"Time frame: "<<k<<endl;
			boundry = changeMap(boundry,false);
            print(boundry);
			k=k+1;
			cout<<flush;
			printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		}
		// vehicle p = vehicle();
		// p.y=1;
		// p.type="<C>";
		// p.updatelen();
		// p.maxspeed = 2.0;
		// p.v=1.0;
		// p.a=.1;

		// objs.push_back(p);
		boundry = enableRedLight(boundry);
		while(k<=50){
			usleep(180000);
			cout<<"\b";
			cout<<"Time frame: "<<k<<endl;
			boundry = changeMap(boundry,true);
            print(boundry);
			k=k+1;
			cout<<flush;
			printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		}
		boundry = disableRedLight(boundry);
		while(k<=70){
			usleep(180000);
			cout<<"\b";
			cout<<"Time frame: "<<k<<endl;
			boundry = changeMap(boundry,false);
            print(boundry);
			k=k+1;
			cout<<flush;
			printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		}

		// boundry = enableRedLight(boundry);
        // while(k<=60){
		// 	usleep(180000);
		// 	cout<<"\b";
		// 	cout<<"Time frame: "<<k<<endl;
		// 	boundry = changeMap(boundry,true);
        //     print(boundry);
		// 	k=k+1;
		// 	cout<<flush;
		// 	printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		// }
        // boundry = disableRedLight(boundry);
        // while(k<=100){
		// 	usleep(180000);
		// 	cout<<"\b";
		// 	cout<<"Time frame: "<<k<<endl;
		// 	boundry = changeMap(boundry,false);
        //     print(boundry);
		// 	k=k+1;
		// 	cout<<flush;
		// 	printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		// }
		cout<<"Time frame: "<<k-1<<endl;
		print(boundry);
	}
}

void controller(){
	Vector_Matrix_Float mainframe = (getBoundry());	
	translate(mainframe,1,1); // 1 and 1 for initial position of car
	//translate(mainframe,2,1);
}

int main(int argc, char const *argv[])
{
	controller();
	cout << objs.size() << endl;
    return 0;
}