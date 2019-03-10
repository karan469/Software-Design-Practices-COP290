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

// Prints the boundry
void boundry(){
	Vector_Matrix_Float b(5,vector<char>(10,' '));
	for(int i=0;i<b.size();i++){
		for(int j=0;j<b[0].size();j++){
			if(i*j==0 || (b.size()-1-i)*(b[0].size()-1-j)==0){
				b[i][j]='-';
			} else {
				b[i][j] = ' ';
			}
		}
	}
	print(b);
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

// this version translates three vehicles but manually
// void translate(Vector_Matrix_Float boundry){

// 	Vector_Matrix_Float bou = boundry;
// 	int a=1,b=2,c=6;
// 	bou[1][a]='0';
// 	bou[2][b]='0';
// 	bou[3][c]='0';
// 	while(a<bou[0].size()-1 || b<bou[0].size()-1 || c<bou[0].size()-1){
// 		sleep(1);
// 		bou[1][a]='0';
// 		bou[2][b]='0';
// 		bou[3][c]='0';
// 		cout<<"\b";
// 		print(bou);
// 		a++;
// 		b++;
// 		c++;
// 		bou[1][a-1] = ' ';bou[2][b-1] = ' ';bou[3][c-1] = ' ';
// 		cout<<flush;
// 		//printf("\033c");
// 	}
// }

bool emptyLane(Vector_Matrix_Float boundry, int lane){
	if(lane<= boundry.size()-2 && lane>= 1){
		for(int i=1;i<= boundry[lane].size()-2;i++){
			if(boundry[lane][i] == '0') return false;
		}
	} else {cout<<"Crossed the boundry mate..";}
	return true; 
}

Vector_Matrix_Float incrementVehicles(Vector_Matrix_Float lousy){
	Vector_Matrix_Float boundry = lousy;
	for(int i=1;i<boundry.size()-1;i++){
		for(int j=boundry[0].size()-2;j>0;j--){
			if(boundry[i][j]!=' '){
				if(j+1!=boundry[0].size()-1) boundry[i][j+1] = boundry[i][j];
				boundry[i][j]=' ';
			}
		}
	}
	return boundry;
}

int countVehiclesInLane(Vector_Matrix_Float lousy, int q){
	Vector_Matrix_Float boundry = lousy;
	if(q>=1 && q<boundry.size()-1){
		int count = 0;
		for(int i=1;i<boundry[0].size()-1;i++){
			if(boundry[q][i]!= ' '){
				count = count + 1;
			}
		}
		return count;
	}
	return -1;
}

string checkLaneChangeOptions(Vector_Matrix_Float lousy, int a, int b){
	if(lousy[a][b]!= ' ' && lousy[a+1][b]==' ' && lousy[a-1][b]==' '){
		return "both";
	} else if(lousy[a][b]!= ' ' && lousy[a+1][b]==' ' && lousy[a-1][b]!=' '){
		return "right";
	} else if(lousy[a][b]!= ' ' && lousy[a+1][b]!=' ' && lousy[a-1][b]==' '){
		return "left";
	} else {
		return "neither";
	}
	return "neither";
}

Vector_Matrix_Float changeMap(Vector_Matrix_Float lousy){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));

	Vector_Matrix_Float boundry = lousy;
	
	// Increment every vehicle in each frame
	boundry = incrementVehicles(boundry);
	
	// Introduce a vehicle when lane empty
	for(int p=1;p<boundry.size()-1;p++){
		if(emptyLane(boundry, p)){
			boundry[p][1]='0';
		}
	}

	// Introduce a new vehicle with (probably) probability of 50%
	for(int k=1;k<boundry.size()-1;k++){
		if(boundry[k][1]==' ' && rand()/rand_max<0.5){
			boundry[k][1]='0';
		}
	}

	// Change Lane with a probability of 90%
	float changeLaneFrequency = 1.0;
	for(int y=1;y<boundry.size()-1;y++){
		for(int r=1;r<boundry[0].size()-1;r++){
			if(checkLaneChangeOptions(boundry, y, r)=="both" && countVehiclesInLane(boundry, y+1)<=countVehiclesInLane(boundry, y-1) && countVehiclesInLane(boundry, y)<=countVehiclesInLane(boundry, y+1) && rand()/rand_max < changeLaneFrequency){
				// Can go in both directions but going right because less vehicles there
				boundry[y+1][r] = boundry[y][r];
				boundry[y][r] = ' ';
			} else if (checkLaneChangeOptions(boundry, y, r)=="both" && countVehiclesInLane(boundry, y+1)>countVehiclesInLane(boundry, y-1) && rand()/rand_max < changeLaneFrequency){
				// Can go in both directions but going left because less vehicles there
				boundry[y-1][r] = boundry[y][r];
				boundry[y][r] = ' ';
			} else if(checkLaneChangeOptions(boundry, y, r)=="left" && countVehiclesInLane(boundry, y)<=countVehiclesInLane(boundry, y-1) && rand()/rand_max < changeLaneFrequency){
				// Go left
				boundry[y-1][r] = boundry[y][r];
				boundry[y][r] = ' ';
			} else if(checkLaneChangeOptions(boundry, y, r)=="right" && countVehiclesInLane(boundry, y)<=countVehiclesInLane(boundry, y+1) && rand()/rand_max < changeLaneFrequency){
				// Go right
				boundry[y+1][r] = boundry[y][r];
				boundry[y][r] = ' ';
			}
		}
	}



	return boundry;
}

// Vector_Matrix_Float changeMap(Vector_Matrix_Float lousy){
// 	std::random_device rd;
// 	std::mt19937 gen(rd());
// 	std::uniform_real_distribution<> dis(0, 1);

// 	Vector_Matrix_Float boundry = lousy;

// 	// increment evry vehicle in frame
// 	boundry = incrementVehicles(boundry);

// 	// if empty lane introduce a vehicle
// 	for(int q=1;q<=boundry.size()-2;q++){
// 		if(emptyLane(boundry, q)==true && dis(gen)<0.9){
// 			boundry[q][1] = '0';
// 		}
// 	}
	
// 	//introduce a new vehicle adjesant to front vehicle with 30% probability
// 	// for(int a=0;a<boundry.size();a++){
// 	// 	if(boundry[a][2]=='0' && dis(gen)<0.3){
// 	// 		boundry[a][1]='0';
// 	// 	}
// 	// }

// 	//with 50% probability, if 1/3rd row is empty(not the whole lane) then introduce a new vehicle.
// 	if(dis(gen)<0.7){
// 		int tempCount = 0;
// 		int tempCount1 = 0;
// 		int tempCount2 = (rand()%(boundry.size()-2)); //random lane
// 		for(int h=1;h<(boundry[0].size()/4)+1;h++){
// 			if(boundry[tempCount2][h]==' ') tempCount++;
// 			tempCount1++;
// 		}
// 		if(tempCount==tempCount1 && emptyLane(boundry, tempCount2)==false){
// 			boundry[tempCount2][1] = '0';
// 		}
// 	} else {
// 		//introduce a new vehicle adjesant to front vehicle with 30%/100% probability
// 		for(int a=0;a<boundry.size();a++){
// 			if(boundry[a][2]=='0' ){
// 				boundry[a][1]='0';
// 			}
// 		}
// 	}

// 	// insert probability of having a clear lane (very less)
// 	// takeover
// 	// change Lanes
// 	// speed high
// 	return boundry;
// }

// this version moves only one vehicle --> ideal function
// void translate(Vector_Matrix_Float boundry, int a, int b){
// 	int k = b;
// 	if(a*b==0 || (boundry.size()-1-a)*(boundry[0].size()-1-b)==0){
// 		// leave it empty
// 	} else {
// 		while(k>0){
// 			sleep(1);
// 			boundry[a][k] = '0';
// 			if(k-1!=0) boundry[a][k-1] = ' '; // removing the trailing zeros
// 			cout<<"\b";
// 			print(boundry);
// 			k++;	
// 			cout<<flush;
// 			// printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
// 		}
// 	}
// }

// this version moves only one vehicle --> ideal function version 2.0
void translate(Vector_Matrix_Float boundry, int a, int b){
	int k = b;
	if(a*b==0 || (boundry.size()-1-a)*(boundry[0].size()-1-b)==0){
		// leave it empty
	} else {
		boundry[a][k] = '0';
		print(boundry);
		printf("\033c");
		while(k>0){
			sleep(1.5);
			// boundry[a][k] = '0';
			// if(k-1!=0) boundry[a][k-1] = ' '; // removing the trailing zeros
			cout<<"\b";
			print(changeMap(boundry));
			boundry = changeMap(boundry);
			k++;
			cout<<flush;
			printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		}
	}
}

void controller(){
	Vector_Matrix_Float mainframe = getBoundry();	
	translate(mainframe,2,1); // 1 and 1 for initial position of car
	//translate(mainframe,2,1);
}

int main(int argc, char const *argv[])
{
	//boundry(); // displays boundry
	
	// time_t now = time(0);
	// tm* localtm = localtime(&now);
	// cout<< now << endl;

	controller();
	

	// Vector_Matrix_Float b = getBoundry();
	// b[1][7] = '0';
	// b[1][6] = '0';
	// b[1][1] = '0';
	// b[5][5] = '0';
	// b[4][7] = '0';
	// print(b);
	// cout<<checkLaneChangeOptions(b, 5, 5);
	// cout<<endl;
	// print(changeMap(b));
	// cout<<endl<<countVehiclesInLane(b,2)<<endl; // Checking the semantics of function
	// cout<<emptyLane(b,0)<<endl;
}
