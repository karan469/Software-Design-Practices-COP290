#ifndef INCREMENTVEHICLE_H
#define INCREMENTVEHICLE_H
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
#include "creation.h"
using namespace std;

#define Vector_Matrix_Float vector<vector<char>>

vector<vector<int>> income(10,vector<int>(3,0));

float greaterinthree(float a,float b, float c)
{
    if(a>b){
        if(a>c) return a;
        else{ return c;}
    }
    else{
        if(b>c) return b;
        else{ return c;}
    }
}

float spaceForward(vehicle* veh, string side, Vector_Matrix_Float boundry,bool* colhappen,bool* sidebar)
{
    int n=0;
    int sp=0;
    float dis=0.0;
    if(side == "left") 
    {
        n=-1;
        if(veh->y==1) {
            *sidebar = true;
            return 0.0;
        }
    }
    else if(side=="right")
    {
        n=1;
        if(veh->y==boundry.size()-2) {
            *sidebar = true;
            return 0.0;
        }
    }
    else n=0;

    vector<char> laneAty = boundry[veh->y+n];//lane at y
    
    if(veh->x2<=0){
        for(int j = veh->x1+1; j < laneAty.size(); j++)
        {
            if(laneAty[j]==' ') dis+=1.0;
            else if(laneAty[j]=='#'){
                *colhappen = true;
                break; 
            }
            else break;
        }
    }
    else{
        for(int j = veh->x2; j < laneAty.size(); j++)
        {
            //need to write the condition for the bike to stand on this | 
            //for this 
            //1. make the bike move forward when there is |
            //2. make bike then not to move forward because then there will be no obstruction
            //2.a one way to make the bike proposed displacement to zero if it is on the 
            //          conditions to be checked
            //          1. red light
            //          2. on this | i.e; at control.redlight_pos in this code
            //First get on this
            //condition if at j there is | and it is bike
            
            bool bikecondition = (j==veh->x1+1 &&j==control.redlight_pos && laneAty[j]=='|' && veh->type=="B");
            
            if((laneAty[j]==' '&&j>veh->x1)) dis+=1.0;
            else if(laneAty[j]=='#'){
                *colhappen = true;
                break; 
            }
            else if(j>veh->x1){
                if(bikecondition) dis+=1.0;
                break;
            }
            if(laneAty[j]==' '&&j<=veh->x1&&n!=0) sp+=1;
        }
        if(n==1) {
            if(sp==veh->type.length())veh->rigspace = true; else false; 
        }
        if(n==-1) {
            if(sp==veh->type.length())veh->lefspace = true; else false; 
        }
    }
    return dis;
}

Vector_Matrix_Float goforward(float x, vehicle* veh, string side, Vector_Matrix_Float boundry,vector<vehicle>::iterator del)
{
    int n=0;
    int y = veh->y;
    float dis=0.0;
    if(side == "left") 
    {
        n = -1;
        y -= 1;
    }
    else if(side=="right")
    {
        n = 1;
        y += 1;
    }
    else n=0;

    // veh->x1 -= round(x);
    if((rand()/RAND_MAX)<0.03){    
        veh->x1+=round(x);
    } else {       
        veh->x1-=round(x);
    }
    veh->x2 = round(veh->x1-veh->length+1.0);
    
    if (veh->x2>0 && veh->x1<boundry[veh->y+n].size()-1) {
        int c=0;
        for(int a = (int)veh->x2; a <= (int)veh->x1; a++)
        {
            
            boundry[veh->y+n][a]=veh->type[c];  
            c++;      
        }
    }
    else if (veh->x2<=0)
    {
        int c=0;
        for(int a = 1; a <= (int)veh->x1; a++)
        {
            boundry[veh->y+n][a]=veh->type[c];  
            c++;      
        }
    }
    else if (veh->x2>=boundry[veh->y+n].size())
    {
        // objs.erase(del);
    }
    else if(veh->x1>=boundry[veh->y+n].size()-1)
    {
        int c=0;
        for(int a = (int)veh->x2; a <= boundry[veh->y+n].size()-2; a++)
        {
            boundry[veh->y+n][a]=veh->type[c];  
            c++;      
        }
    }
    veh->y=y;
    if(veh->v>x) veh->v = x;
    return boundry;
}

Vector_Matrix_Float incrementVehicle(Vector_Matrix_Float lousy, bool red){
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	Vector_Matrix_Float boundry = lousy;
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));
    vector<vehicle>::iterator del; 
    del = objs.begin();
    for(int i = 0; i < objs.size(); i++)
    {   
        bool collide=false;
        vehicle* veh = &objs[i];
        veh->updatespeed(1.0);
        float x = veh->lentogo(1.0);//len if there is no vehicle
        veh->lefspace = false; veh->rigspace = false;
        vector<char> laneAty = boundry[veh->y];
        vector<char> laneAtleft = boundry[veh->y-1];
        vector<char> laneAtright = boundry[veh->y+1];//lane at y
        veh->inWay=0.0;veh->riglo=0.0;veh->leflo=0.0;
        bool colhappen=false;
        bool sidebar = false;
        veh->inWay = spaceForward(veh,"inWay",boundry,&colhappen,&sidebar);
        veh->leflo = spaceForward(veh,"left",boundry,&colhappen,&sidebar);
        veh->riglo = spaceForward(veh,"right",boundry,&colhappen,&sidebar);

        int khaale = 0;
        for(int i = control.redlight_pos;i>=1;i--)
        {
            if(boundry[veh->y][i]==' '){
                
                break;
            }
            khaale+=1;
        }
        bool bikestop = (veh->type=="B" && veh->x1==control.redlight_pos && red);
        if(bikestop&&rand()/rand_max<.95) x=0;

        if (veh->x2>0 && veh->x1<laneAty.size()-1) {
            int c=0;
            if(boundry[veh->y][veh->x1]=='#') collide = true;
            for(int a = (int)veh->x2; a <= (int)veh->x1; a++)
            {
                if(boundry[veh->y][a]==veh->type[0]||boundry[veh->y][a]=='|'&&!collide) boundry[veh->y][a]=' ';  
                else
                {   
                    boundry[veh->y][a]='#';collide=true;
                }
                if(red) {if(boundry[veh->y][control.redlight_pos]!='B')boundry[veh->y][control.redlight_pos]='|';}
                
                c++;      
            }
        }
        else if (veh->x2<=0)
        {
            int c=0;
            for(int a = 1; a <= (int)veh->x1; a++)
            {
                boundry[veh->y][a]=' ';  
                
                c++;      
            }
        }
        else if(veh->x1>=boundry[veh->y].size()-1)
        {
            int c=0;
            for(int a = (int)veh->x2; a <= boundry[veh->y].size()-2; a++)
            {
                boundry[veh->y][a]=' ';  
                c++;      
            }
        }
        bool nostandcollide = true;
        if((veh->x1+khaale >= control.redlight_pos && veh->x1 <= (control.redlight_pos - 2)) && red)
        {
            if(rand()/rand_max<=0.5 && veh->type=="CC" && veh->rotleft==false && veh->rotleft==false) veh->rotleft = true; else veh->rotright = true;
        }
        if(collide){
            veh->v = 0;veh->a = 0;x=0;
        }
        else if((veh->inWay >= x || (veh->inWay==0&&veh->riglo==0&&veh->leflo==0&&veh->x1>=boundry[veh->y].size()-2 ))||(rand()/rand_max<0.03 && (!(veh->x1+khaale >= control.redlight_pos && veh->x1 < control.redlight_pos))&& !colhappen))
        {
            boundry = goforward(x,veh,"inWay",boundry,del);
            if(x>1) {veh->rotright = false; veh->rotleft = false;}
        }
        else
        {
            if((not(not(veh->inWay>=veh->leflo)&&veh->lefspace||(rand()/rand_max<0.03&&!sidebar&&(!(veh->x1+khaale>=control.redlight_pos && veh->x1 <= control.redlight_pos)))))){
                if((not(not(veh->inWay>=veh->riglo)&&veh->rigspace||(rand()/rand_max<0.03&&!sidebar&&(!(veh->x1+khaale>=control.redlight_pos && veh->x1 <= control.redlight_pos))))))
                {
                    boundry = goforward(veh->inWay,veh,"inWay",boundry,del);
                    if(x>1) {veh->rotright = false; veh->rotleft = false;}
                }
                else
                {
                    if(veh->riglo>=x) boundry = goforward(x,veh,"right",boundry,del);
                    else boundry = goforward(veh->riglo,veh,"right",boundry,del);
                    veh->rotright = true; veh->rotleft = false;
                }
            }
            else{
                if(veh->leflo>=veh->riglo)
                {
                    if(veh->leflo>=x) boundry = goforward(x,veh,"left",boundry,del);
                    else boundry = goforward(veh->leflo,veh,"left",boundry,del);
                    veh->rotright = false; veh->rotleft = true;
                }
                else { 
                    if(veh->riglo>=x) boundry = goforward(x,veh,"right",boundry,del);
                    else boundry = goforward(veh->riglo,veh,"right",boundry,del);
                    veh->rotright = true; veh->rotleft = false;
                }
            }
        }
        
        if(veh->x2 == control.Road_Length + 2) objs.erase(del);
        
        
        ++del;
    }
    
	return boundry;
}


#endif