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

 

Vector_Matrix_Float incrementVehicle(Vector_Matrix_Float lousy, bool red){
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	Vector_Matrix_Float boundry = lousy;
	
	double rand_max = RAND_MAX;
	srand((int)time(NULL));
    auto del = objs.begin();
    for(int i = 0; i < objs.size(); i++)
    {   
        vehicle* veh = &objs[i];
        veh->updatespeed(1.0);
        float x = veh->lentogo(1.0);//len if there is no vehicle
        veh->inWay=0.0;
        vector<char> laneAty = boundry[veh->y];//lane at y
        for(int j = veh->x1+1; j < laneAty.size(); j++)
        {
            if(laneAty[j]==' ') veh->inWay+=1.0;
            else break; 
        }

        vector<char> laneAtleft = boundry[veh->y-1];
        vector<char> laneAtright = boundry[veh->y+1];
        veh->leflo=0.0;veh->riglo=0.0;//as distance to measured from start

        if(veh->y!=1 && veh->y!=boundry.size()-2)
        {
            for(int j = veh->x1+1; j < laneAtleft.size(); j++)
            {
                if(laneAtleft[j]==' ') veh->leflo+=1.0;
                else break; 
            }
            for(int j = veh->x1+1; j < laneAtright.size(); j++)
            {
                if(laneAtright[j]==' ') veh->riglo+=1.0;
                else break; 
            }
        }
        else if(veh->y==1)
        {
            for(int j = veh->x1+1; j < laneAtright.size(); j++)
            {
                if(laneAtright[j]==' ') veh->riglo+=1.0;
                else break; 
            }
        }
        else if(veh->y==boundry.size()-2)
        {
            for(int j = veh->x1+1; j < laneAtleft.size(); j++)
            {
                if(laneAtleft[j]==' ') veh->leflo+=1.0;
                else break; 
            }
        }
        // cout<<veh->type<<veh->x1<<" x:"<<x<<endl;
        // cout<<veh->type<<" inway:"<<veh->inWay << endl;
        // cout<<veh->type<<" riglo:"<<veh->riglo << endl;
        // cout<<veh->type<<" leflo:"<<veh->leflo << endl;
        //Till this part I have calculated
        //right,left and his own lane space respectively in riglo,leflo and inWay
        //lentogo(in x) according to acceleration is also there

        //see if vehicle has collided
        bool backcollide = false;
        bool forcollide = false;
        veh->lefspace=true;
        veh->rigspace=true;
        if (veh->x2>0 && veh->x1<laneAty.size()-1) {
            int c=0;
            // if(veh->x1+1<laneAty.size()-1)
            // {
            //     if(boundry[veh->y][veh->x1+1]!=' '&&boundry[veh->y][veh->x1+1]!='<'&&boundry[veh->y][veh->x1+1]!='|') {
            //         forcollide = true;
            //         veh->v=0;veh->a=0;
            //     }
            // }
            for(int a = (int)veh->x2; a <= (int)veh->x1; a++)
            {
                // if(boundry[veh->y][a]!=veh->type[c]&&boundry[veh->y][a]!='|'&&c<=1)
                // { backcollide = true;veh->v=0;veh->a=0;}
                boundry[veh->y][a]=' ';  
                if(red) boundry[veh->y][15]='|';
                
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
            // if(veh->x1+1<laneAty.size()-1)
            // {
            //     if(boundry[veh->y][veh->x1+1]!=' '||boundry[veh->y][veh->x1+1]!='<'||boundry[veh->y][veh->x1+1]!='|') {
            //         forcollide = true;
            //         // cout << boundry[veh->y][veh->x1+1] <<" ";
            //         veh->v=0;veh->a=0;
            //     }
            // }
            for(int a = (int)veh->x2; a <= boundry[veh->y].size()-2; a++)
            {
                // if(boundry[veh->y][a]!=veh->type[c]) 
                // { backcollide = true;veh->v=0;veh->a=0;}
                boundry[veh->y][a]=' ';  
                
                c++;      
            }
        }
        //Lets make our car move
        if((veh->inWay >= x || (veh->inWay==0&&veh->riglo==0&&veh->leflo==0&&veh->x1>=boundry[veh->y].size()-2 )))
        {
            //then we have to make car to travel this much distance
            
            if(backcollide || forcollide) 
            {
                // cout << " crashed "<<backcollide<<" "<<forcollide << endl;
            }
            else{
            veh->x1+=round(x);
            veh->x2=round(veh->x1-veh->length+1.0);
            }
            if (veh->x2>0 && veh->x1<boundry[veh->y].size()-1) {
                int c=0;
                for(int a = (int)veh->x2; a <= (int)veh->x1; a++)
                {
                    if(c==veh->type.size()-1&&forcollide) boundry[veh->y][a]='#';
                    else if(c==0&&backcollide) boundry[veh->y][a]='#';
                    else boundry[veh->y][a]=veh->type[c];  
                    c++;      
                }
            }
            else if (veh->x2<=0)
            {
                int c=0;
                // int c=veh->type.size()-veh->x2-1;
                for(int a = 1; a <= (int)veh->x1; a++)
                {
                    boundry[veh->y][a]=veh->type[c];  
                    c++;      
                }
            }
            else if (veh->x2>=boundry[veh->y].size()-1)
            {
                objs.erase(del);
            }
            else if(veh->x1>=boundry[veh->y].size()-1)
            {
                int c=0;
                for(int a = (int)veh->x2; a <= boundry[veh->y].size()-2; a++)
                {
                    boundry[veh->y][a]=veh->type[c];  
                    c++;      
                }
            }
            
            //vehicle incremented according to acceleration
            //lets go to the lane change option
            
        }
        else
        {
            //inway leflo riglo
            if(veh->inWay>=veh->leflo){
                if(veh->inWay>=veh->riglo)
                {
                    // veh->inWay;
                    if(backcollide || forcollide) 
                    {
                        // cout << " crashed "<<backcollide<<" "<<forcollide << endl;
                    }
                    else{
                        veh->x1+=round(veh->inWay);
                        veh->x2=round(veh->x1-veh->length+1.0);
                    }
                
                    if (veh->x2>0 && veh->x1<boundry[veh->y].size()-1) {
                        int c=0;
                        for(int a = (int)veh->x2; a <= (int)veh->x1; a++)
                        {
                            boundry[veh->y][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    else if (veh->x2<=0)
                    {
                        int c=0;
                        for(int a = 1; a <= (int)veh->x1; a++)
                        {
                            boundry[veh->y][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    else if (veh->x2>=boundry[veh->y].size()-1)
                    {
                        objs.erase(del);
                    }
                    else if(veh->x1>=boundry[veh->y].size()-1)
                    {
                        int c=0;
                        for(int a = (int)veh->x2; a <= boundry[veh->y].size()-2; a++)
                        {
                            boundry[veh->y][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    veh->v=veh->inWay;
                }
                else { 
                    // veh->riglo;
                    if(backcollide || forcollide) 
                    {
                        // cout << " crashed "<<backcollide<<" "<<forcollide << endl;
                    }
                    else{
                        if(veh->riglo>=x) veh->x1+=round(x);
                        else {veh->x1+=round(veh->riglo);veh->v=veh->riglo;}
                        veh->x2=round(veh->x1-veh->length+1.0);
                    }
                    
                
                    if (veh->x2>0 && veh->x1<boundry[veh->y+1].size()-1) {
                        int c=0;
                        for(int a = (int)veh->x2; a <= (int)veh->x1; a++)
                        {
                            boundry[veh->y+1][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    else if (veh->x2<=0)
                    {
                        int c=0;
                        for(int a = 1; a <= (int)veh->x1; a++)
                        {
                            boundry[veh->y+1][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    else if (veh->x2>=boundry[veh->y+1].size()-1)
                    {
                        objs.erase(del);
                    }
                    else if(veh->x1>=boundry[veh->y+1].size()-1)
                    {
                        int c=0;
                        for(int a = (int)veh->x2; a <= boundry[veh->y+1].size()-2; a++)
                        {
                            boundry[veh->y+1][a]=veh->type[c];  
                            c++;      
                        }round(x);
                    }
                    veh->y+=1;
                }
            }
            else{
                if(veh->leflo>=veh->riglo)
                {
                    // veh->leflo;
                    if(backcollide || forcollide) 
                    {
                        // cout << " crashed "<<backcollide<<" "<<forcollide << endl;
                        
                    }
                    else{
                        if(veh->leflo>=x) veh->x1+=round(x);
                        else {veh->x1+=round(veh->leflo);veh->v=veh->leflo;}
                        veh->x2=round(veh->x1-veh->length+1.0);
                    }
                    // if(veh->leflo>=x) veh->x1+=round(x);
                    // else {veh->x1+=round(veh->leflo);veh->v=veh->leflo;}
                    // veh->x2=round(veh->x1-veh->length+1.0);
                
                    if (veh->x2>0 && veh->x1<boundry[veh->y-1].size()-1) {
                        int c=0;
                        for(int a = (int)veh->x2; a <= (int)veh->x1; a++)
                        {
                            boundry[veh->y-1][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    else if (veh->x2<=0)
                    {
                        int c=0;
                        for(int a = 1; a <= (int)veh->x1; a++)
                        {
                            boundry[veh->y-1][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    else if (veh->x2>=boundry[veh->y-1].size()-1)
                    {
                        objs.erase(del);
                    }
                    else if(veh->x1>=boundry[veh->y-1].size()-1)
                    {
                        int c=0;
                        for(int a = (int)veh->x2; a <= boundry[veh->y-1].size()-2; a++)
                        {
                            boundry[veh->y-1][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    veh->y-=1;
                } 
                else { 
                    // veh->riglo;
                    if(backcollide || forcollide) 
                    {
                        // cout << " crashed "<<backcollide<<" "<<forcollide << endl;
                    }
                    else{
                        if(veh->riglo>=x) veh->x1+=round(x);
                        else {veh->x1+=round(veh->riglo);veh->v=veh->riglo;}
                        veh->x2=round(veh->x1-veh->length+1.0);
                    }
                
                    if (veh->x2>0 && veh->x1<boundry[veh->y+1].size()-1) {
                        int c=0;
                        for(int a = (int)veh->x2; a <= (int)veh->x1; a++)
                        {
                            boundry[veh->y+1][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    else if (veh->x2<=0)
                    {
                        int c=0;
                        for(int a = 1; a <= (int)veh->x1; a++)
                        {
                            boundry[veh->y+1][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    else if (veh->x2>=boundry[veh->y+1].size()-1)
                    {
                        objs.erase(del);
                    }
                    else if(veh->x1>=boundry[veh->y+1].size()-1)
                    {
                        int c=0;
                        for(int a = (int)veh->x2; a <= boundry[veh->y+1].size()-2; a++)
                        {
                            boundry[veh->y+1][a]=veh->type[c];  
                            c++;      
                        }
                    }
                    veh->y+=1;
                }
            }
        }
        
        ++del;
    }
    
	return boundry;
}


#endif
