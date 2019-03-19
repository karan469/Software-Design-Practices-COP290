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
#define Vector_Matrix_Float vector<vector<char>>
using namespace std;

// class VehicleMovement {
// 	Private:
// 	int turnstate[] = {-1,0,1};
// 	int maxSpeed;
// 	int speed;
// 	Public:
// 	void changeSpeed(int a){
// 		speed = a;
// 	}
// 	void changeTurnState(int a)/*can be 1 2 or 3*/{
		
// 	}
// }



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
	Vector_Matrix_Float b(10,vector<char>(25,' '));
	for(int i=0;i<b.size();i++){
		for(int j=0;j<b[0].size();j++){
			if(i*j==0 || (b.size()-1-i)*(b[0].size()-1-j)==0){
				b[i][j]='-';
			} else {
				b[i][j] = ' ';
			}
		}
	}

	// trying to remove right boundry
	// for(int h=1;h<b.size()-1;h++){
	// 	if(b[h][b[0].size()-1]=='-') b[h][b[0].size()-1] =' ';
	// }
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


bool emptyLane(Vector_Matrix_Float boundry, int lane){
	if(lane<= boundry.size()-2 && lane>= 1){
		for(int i=1;i<= boundry[lane].size()-2;i++){
			if(boundry[lane][i] != ' ' && boundry[lane][i]!='|') return false;
		}
	} else {cout<<"Crossed the boundry mate..";}
	return true; 
}

bool vehicleAtLight(Vector_Matrix_Float lousy, int lane){
	Vector_Matrix_Float boundry = lousy;
	for(int i=1;i<boundry[0].size()-1;i++){
		if(boundry[lane][i]=='|' && boundry[lane][i-1]!=' '){
			return true;
		}
	}
	return false;
}

bool emptyLaneInFront(Vector_Matrix_Float lousy, int a, int b){

	if(lousy[a][15]=='|'){
		if(b<15){
			int count = 0;
			for(int t=b+1;t<15;t++){
				if(lousy[a][t]==' ') count++;
			}
			if(count != (15-b-1)) return false;
		} else {
			int count = 0;
			for(int t=b+1;t<lousy[0].size()-1;t++){
				if(lousy[a][t]==' ') count++;
			}
			if(count!=(lousy[0].size()-1-b-1)) return false;
		}	
	}
	return true;
}

int lesserInLeftThanRightLane(Vector_Matrix_Float lousy, int a, int b){
	int countLeft = 0;
	int countRight = 0;

	if(lousy[a][15]=='|'){
		if(b<15){
			for(int t=b+1;t<15;t++){
				if(lousy[a-1][t]==' ') countLeft++;
			}
			//if(count != (15-b-1)) return false;
		} else {
			for(int t=b+1;t<lousy[0].size()-1;t++){
				if(lousy[a-1][t]==' ') countLeft++;
			}
			//if(count!=(lousy[0].size()-1-b-1)) return false;
		}
	}

	if(lousy[a][15]=='|'){
		if(b<15){
			for(int t=b+1;t<15;t++){
				if(lousy[a+1][t]==' ') countRight++;
			}
			//if(count != (15-b-1)) return false;
		} else {
			for(int t=b+1;t<lousy[0].size()-1;t++){
				if(lousy[a+1][t]==' ') countRight++;
			}
			//if(count!=(lousy[0].size()-1-b-1)) return false;
		}
	}
	if(countRight<countLeft) return 1;
	else if(countRight==countLeft) return -1;
	return 0;
}

Vector_Matrix_Float incrementVehiclesWhenGreenLight(Vector_Matrix_Float lousy){
	Vector_Matrix_Float boundry = lousy;
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));

	for(int i=1;i<boundry.size()-1;i++){
		for(int j=boundry[0].size()-2;j>0;j--){
			if(boundry[i][j]!=' ' && (boundry[i][j+1]==' ' || boundry[i][j+1]=='-') && rand()/rand_max<0.9){
				if(boundry[i][j+1]=='-'){
					boundry[i][j]=' ';
				} else {
					boundry[i][j+1]=boundry[i][j];
					boundry[i][j]=' ';
				}
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
	
	if(lousy[a][b]!=' ' || lousy[a][b]!='|')
	{	if(emptyLaneInFront(lousy,a,b)==1){return "neither";}
		else if(lesserInLeftThanRightLane(lousy,a,b)==1){return "left";}
		else if(lesserInLeftThanRightLane(lousy,a,b)==0){return "right";}
		else if(lesserInLeftThanRightLane(lousy,a,b)==-1){return "neither";}
		else if(lousy[a+1][b]==' ' && lousy[a-1][b]!=' '){return "right";}
		else if(lousy[a+1][b]!=' ' && lousy[a-1][b]==' '){return "left";}
	}
	return "left";
}

Vector_Matrix_Float changeMap(Vector_Matrix_Float lousy){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));
	char allVehicles[] = {'T', 'C','B'};

	Vector_Matrix_Float boundry = lousy;
	
	// Increment every vehicle in each frame
	boundry = incrementVehiclesWhenGreenLight(boundry);
	
	// Introduce a vehicle when lane empty
	for(int p=1;p<boundry.size()-1;p++){
		if(emptyLane(boundry, p)){
			boundry[p][1]=' '; //changed on 02:04 pm Monday
		}
	}

	// Introduce a new vehicle with (probably) probability of 15%
	for(int k=1;k<boundry.size()-1;k++){
		if(boundry[k][1]==' ' && rand()/rand_max<0.15){
			boundry[k][1]=allVehicles[(int)floor((rand()/rand_max)*3)];
		}
	}

	// Change Lane with a probability of 95%
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
			} else if(checkLaneChangeOptions(boundry, y, r)=="neither"){
				boundry[y][r] = boundry[y][r];
			}
		}
	}



	return boundry;
}

// Change map in case of incrementing the vehicles which are not immediate on traffic light
Vector_Matrix_Float changeMapNew(Vector_Matrix_Float lousy){
	Vector_Matrix_Float boundry = lousy;
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));
	for(int i=1;i<boundry.size()-1;i++){
		if(vehicleAtLight(boundry, i)==true){
			for(int j=boundry[0].size()-2;j>0;j--){
				if(boundry[i][j]!='|' && boundry[i][j+1]!='|'){
					if(boundry[i][j+1]==' '){
						boundry[i][j+1] = boundry[i][j];
						boundry[i][j] = ' ';
					}
				}	
			}
		} else {
			for(int j=boundry[0].size()-2;j>0;j--){
				if(boundry[i][j]!='|' && boundry[i][j]!=' '){
					if(boundry[i][j+1]=='-'){
						boundry[i][j]=' ';
					} else if(boundry[i][j+1]==' ') {
						boundry[i][j+1]=boundry[i][j];
						boundry[i][j]=' ';
					}
				}
			}
		}
	}

	// Change Lane with a probability of 95% // Check its semantics, i think its faulty
	float changeLaneFrequency = 1.0;
	for(int y=1;y<boundry.size()-1;y++){
		for(int r=boundry[0].size()-2;r>=1;r--){
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
			} else if(checkLaneChangeOptions(boundry, y, r)=="neither"){
				boundry[y][r] = boundry[y][r];
			}
		}
	}

	return boundry;
}


// this version moves only one vehicle --> ideal function version 2.0
void translate(Vector_Matrix_Float boundry, int a, int b){
	int k = b;
	if(a*b==0 || (boundry.size()-1-a)*(boundry[0].size()-1-b)==0){
		// leave it empty
	} else {
		boundry[a][k] = 'C';
		
		cout<<"Time frame: "<<0<<endl;
		
		print(boundry);
		printf("\033c");

		while(k<30){
			usleep(180000);
			cout<<"\b";
			cout<<"Time frame: "<<k<<endl;
			print(changeMap(boundry));
			boundry = changeMap(boundry);
			k++;
			cout<<flush;
			printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		}
		boundry = enableRedLight(boundry);
		while(k<40){
			usleep(180000);
			cout<<"\b";
			cout<<"Time frame: "<<k<<endl;
			print(changeMapNew(boundry));
			boundry = changeMapNew(boundry);
			k++;
			cout<<flush;
			printf("\033c");
		}
		boundry = disableRedLight(boundry);
		while(k>0){
			usleep(200000);
			cout<<"\b";
			cout<<"Time frame: "<<k<<endl;
			print(changeMap(boundry));
			boundry = changeMap(boundry);
			k++;
			cout<<flush;
			printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		}
		cout<<"Time frame: "<<k<<endl;
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
	

	// Vector_Matrix_Float asd= enableRedLight(getBoundry());
	// asd[4][4]='T';
	// asd[4][10]='C';
	// asd[4][17]='B';
	// asd[5][7] = 'B';
	// asd[5][6] = 'T';
	// asd[3][13] = 'B';
	// print(asd);
	// cout<<endl;
	// cout<<emptyLaneInFront(asd,4,17)<<endl;
	// cout<<lesserInLeftThanRightLane(asd,4,17)<<endl;

	// print(disableRedLight(asd));


	cout << "\033[1;31mbold red text\033[0m\n";
}