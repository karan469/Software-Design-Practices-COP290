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
        if(boundry[i][15]==' ')	boundry[i][15] = '|'; // Change its colour to RED
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


Vector_Matrix_Float incrementVehiclesWhenGreenLight(Vector_Matrix_Float lousy, bool red){
	Vector_Matrix_Float boundry = lousy;
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));
    bool nred = true;
	for(int i=1;i<boundry.size()-1;i++){
		for(int j=boundry[0].size()-2;j>0;j--){
            
                if(boundry[i][j+1]==' ')
                {
                    if(not(j==15 && red)) boundry[i][j+1]=boundry[i][j];
                    else
                    {
                        if(boundry[i][j]!='|' && boundry[i][j]!=' '){
                            boundry[i][j+1]=boundry[i][j];nred=false;
                            if(boundry[i][j]=='<') nred=true;
                        } 
                        
                    }
                    
                    if(j==15 && red && nred) {boundry[i][j]='|';nred=true;}
                    else boundry[i][j]=' ';
                }
				else if(boundry[i][j+1]=='-'){
					boundry[i][j]=' ';
				} 
		}
	}
	return boundry;
}

vector<vector<int>> income(10,vector<int>(3,0));

Vector_Matrix_Float changeMap(Vector_Matrix_Float lousy,bool red){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));
	string allVehicles[] = {">RC<", ">O<", ">KCURT<", ">SUB<"};

	Vector_Matrix_Float boundry = lousy;
	
	// Increment every vehicle in each frame
	boundry = incrementVehiclesWhenGreenLight(boundry,red);

	// Introduce a new vehicle with (probably) probability of 15%
	for(int k=1;k<boundry.size()-1;k++){
        if(red && boundry[k][1]!=' ');
        else
        {
            if(income[k][0]==0&&income[k][1]==0&&income[k][2]==0)
            {
                boundry[k][1]=' ';
            }
            if (income[k][0]==1) {
                if (income[k][1]==0) {
                    boundry[k][1]=allVehicles[0][income[k][2]];
                    if(income[k][2]==3)
                    {
                        income[k][0]=0;income[k][1]=0;income[k][2]=0;
                    }
                    else{
                        income[k][2]+=1;
                    }
                }
                else if (income[k][1]==1) {
                    boundry[k][1]=allVehicles[1][income[k][2]];
                    if(income[k][2]==2)
                    {
                        income[k][0]=0;income[k][1]=0;income[k][2]=0;
                    }
                    else{
                        income[k][2]+=1;
                    }
                }	
                else if (income[k][1]==2) {
                    boundry[k][1]=allVehicles[2][income[k][2]];
                    if(income[k][2]==6)
                    {
                        income[k][0]=0;income[k][1]=0;income[k][2]=0;
                    }
                    else{
                        income[k][2]+=1;
                    }
                }	
                else if (income[k][1]==3) {
                    boundry[k][1]=allVehicles[3][income[k][2]];
                    if(income[k][2]==4)
                    {
                        income[k][0]=0;income[k][1]=0;income[k][2]=0;
                    }
                    else{
                        income[k][2]+=1;
                    }
                }		
            }
            else if(boundry[k][1]==' ' && rand()/rand_max<0.1){	
                int c = (int)floor((rand()/rand_max)*4);
                boundry[k][1]=allVehicles[c][0];
                income[k][0]=1;income[k][1]=c;income[k][2]=1;
            }
        }
        
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
		
		cout<<"Time frame: "<<k<<endl;
		
		print(boundry);
		printf("\033c");
        k=k+1;
		while(k<=20){
			usleep(180000);
			cout<<"\b";
			cout<<"Time frame: "<<k<<endl;
			boundry = changeMap(boundry,false);
            print(boundry);
			k=k+1;
			cout<<flush;
			printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		}
		boundry = enableRedLight(boundry);
        while(k<=60){
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
        while(k<=100){
			usleep(180000);
			cout<<"\b";
			cout<<"Time frame: "<<k<<endl;
			boundry = changeMap(boundry,false);
            print(boundry);
			k=k+1;
			cout<<flush;
			printf("\033c"); // disabling this will give you discrete time frames -- simple // resets the terminal
		}
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
    return 0;
}
