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
#include <regex>
#include <cstring>
#include <string>
#include "mainv1.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <fstream>
#include <sstream>
#include "creation.h"
using namespace std;
#define Vector_Matrix_Float vector<vector<char>>

//GLOBAL DEFINED VARIABLES//
int countFrames = 0;
Vector_Matrix_Float boundry;
bool redCheck = false;
////////////////////////////

// readConfig() modifies the struct variables present in creation.h
void readConfig(string filename){
	smatch what1;
    std::string line;
    std::ifstream myfile("config.ini");
    if(myfile.is_open()){
        std::cout <<"FILE OPEN " <<std::endl;
        while(getline(myfile, line))
        {
            if(line.substr(0,7)=="Road_Id"){
                string ans = line.substr(10,line.length()-10);
                for(int i=0;i<ans.length();i++){
                	control.Road_Id[i] = ans[i];
                }
                //control.Road_Id = ans;
            } else if (line.substr(0,11)=="Road_Length"){
                control.Road_Length = stoi(line.substr(14,line.length()-14));
            } else if (line.substr(0,10)=="Road_Width"){
                control.Road_Width = stoi(line.substr(13,line.length()-13));
            } else if(line.substr(0,13)=="Max_Speed_Car"){
            	control.maxspeed_car = stoi(line.substr(16,line.length()-16));
            } else if(line.substr(0,14)=="Max_Speed_Bike"){
            	control.maxspeed_bike = stoi(line.substr(17,line.length()-17));
            } else if(line.substr(0,15)=="Max_Speed_Truck"){
            	control.maxspeed_truck = stoi(line.substr(18,line.length()-18));
            } else if(line.substr(0,14)=="Max_Speed_Auto"){
            	control.maxspeed_auto = stoi(line.substr(17,line.length()-17));
            } else if(line.substr(0,18)=="Acceleration_Truck"){
            	control.acc_truck = stoi(line.substr(21,line.length()-21));
            } else if(line.substr(0,17)=="Acceleration_Bike"){
            	control.acc_bike = stoi(line.substr(20,line.length()-20));
            } else if(line.substr(0,16)=="Acceleration_Car"){
            	control.acc_car = stoi(line.substr(19,line.length()-19));
            } else if(line.substr(0,17)=="Acceleration_Auto"){
            	control.acc_auto = stoi(line.substr(20,line.length()-20));
            } else if(line.substr(0,18)=="Road_Red_Light_Pos"){
            	control.redlight_pos = stoi(line.substr(21,line.length()-21));
            } else if(line.substr(0,19)=="1. Green signal for"){
            	control.timefor_signals[0]=stoi(line.substr(22,line.length()-22));
            } else if (line.substr(0,17)=="2. Red signal for"){
            	control.timefor_signals[1]=stoi(line.substr(20,line.length()-20));
            } else if (line.substr(0,19)=="3. Green signal for"){
            	control.timefor_signals[2] = stoi(line.substr(22,line.length()-22));
            }
        
        }

    }
}

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window; 

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}


GLvoid DrawGLScene(GLvoid)
{
	

	countFrames += 1;
	if (countFrames == 60) return;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
	glLoadIdentity();						// Reset The View
	

	glTranslatef(0.0f,-20.0f,-55.0f);
	glRotatef(40.0, -1.0, 0.0, 0.0);
	glRotatef(60.0, 0.0, 0.0, 1.0);
	
	//road draw
	glBegin(GL_QUADS);
		glColor3f(5.0f, 5.0f, 5.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		
	    glVertex3f((float)(control.Road_Length-2), 0.0f, 0.0f);
	    
	    glVertex3f((float)(control.Road_Length-2), (float)(control.Road_Width*2), 0.0f);
	    
	    glVertex3f(0.0f, (float)(control.Road_Width*2), 0.0f);
	glEnd();

	//zebracrossing
	glBegin(GL_QUADS);
		glColor3f(0.498f, 0.501f, 0.529f);
		glVertex3f((float)(control.redlight_pos-1), 0.0f, 0.1f);
		
	    glVertex3f((float)(control.redlight_pos+1), 0.0f, 0.1f);
	    
	    glVertex3f((float)(control.redlight_pos+1), (float)(control.Road_Width*2), 0.1f);
	    
	    glVertex3f((float)(control.redlight_pos-1), (float)(control.Road_Width*2), 0.1f);
	glEnd();


	/////////////////////////////////////////////////////////////
	double rand_max = RAND_MAX;
	srand((int)time(NULL));

	int a=1,b=1;
	if(a*b!=0 && (boundry.size()-1-a)*(boundry[0].size()-1-b)!=0){
		//change it to 180000 immediately, now!!
		usleep(160000);
		cout<<"\b";
		cout<<"Time frame: "<<countFrames<<endl;
		int h1 = control.timefor_signals[0];
		int h2 = control.timefor_signals[1] + h1;

		if(countFrames<h1 || countFrames >h2){
			if(countFrames == h2+1)
			{
				boundry = disableRedLight(boundry);
			}
			redCheck = false;
		} else {
			if(countFrames == h1)
			{
				boundry = enableRedLight(boundry);
			}
			redCheck = true;
		}

		if(redCheck==false){
			boundry = changeMap(boundry,false);
		} 
		else {
			boundry = changeMap(boundry,true);
		}
		
		if(redCheck==false){
			//green light square
			glBegin(GL_QUADS);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f((float)(control.redlight_pos+2), 2.0f, 1.0f);
				
			    glVertex3f((float)(control.redlight_pos+4), 2.0f, 1.0f);
			    
			    glVertex3f((float)(control.redlight_pos+4), 0.0f, 1.0f);
			    
			    glVertex3f((float)(control.redlight_pos+2), 0.0f, 1.0f);
			glEnd();
		} else {
			//redlight square
			glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f((float)(control.redlight_pos+2), 2.0f, 1.0f);
				
			    glVertex3f((float)(control.redlight_pos+4), 2.0f, 1.0f);
			    
			    glVertex3f((float)(control.redlight_pos+4), 0.0f, 1.0f);
			    
			    glVertex3f((float)(control.redlight_pos+2), 0.0f, 1.0f);
			glEnd();
		}

		for(int i = 0; i<objs.size(); i++){
			vehicle veh = objs[i];

			int y = veh.y;
			int r = veh.x1;
			int l = 0;
			if(veh.x2>0){ l = veh.x1-veh.type.length();} else l=0;

			if(boundry[y][r]=='C'){ //this is autorikshaw
				if(veh.rotleft)
				{
					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)+1.0f, 1.0f);
						
						glVertex3f((float)(l), (float)(y+y)+1.0f, 1.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 1.0f);
						
						glVertex3f((float)r, (float)(y+y), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y)+1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y)+1.0f, 1.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 2.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)+1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y)+1.0f, 2.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)+1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)+1.0f, 1.0f);
					glEnd();
					//backface
					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)(l), (float)y+y+1.0f, 1.0f);
						
						glVertex3f((float)(l), (float)(y+y)+1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)+1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)+1.0f, 1.0f);
					glEnd();
					//frintface
					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(r), (float)(y+y), 2.0f);
						
						glVertex3f((float)(r), (float)(y+y), 1.0f);
					glEnd();
				}
				else if(veh.rotright)
				{
					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)-1.0f, 1.0f);
						
						glVertex3f((float)(l), (float)(y+y)-1.0f, 1.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 1.0f);
						
						glVertex3f((float)r, (float)(y+y), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y)-1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y)-1.0f, 1.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 2.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)-1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y)-1.0f, 2.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)-1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)-1.0f, 1.0f);
					glEnd();
					//backface
					glBegin(GL_QUADS);
						glColor3f((188/255), (61/255), (26/255));
						glVertex3f((float)(l), (float)y+y-1.0f, 1.0f);
						
						glVertex3f((float)(l), (float)(y+y)-1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)-1.0f, 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1)-1.0f, 1.0f);
					glEnd();
					//frintface
					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(r), (float)(y+y), 2.0f);
						
						glVertex3f((float)(r), (float)(y+y), 1.0f);
					glEnd();
				}
				else {
					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)(l), (float)(y+y+1), 1.0f);
						
						glVertex3f((float)(l), (float)(y+y), 1.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 1.0f);
						
						glVertex3f((float)r, (float)(y+y), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y), 1.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)y+y, 2.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y), 2.0f);
					glEnd();

					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1), 1.0f);
					glEnd();
					//backface
					glBegin(GL_QUADS);
						glColor3f((188/255), (61/255), (26/255));
						glVertex3f((float)(l), (float)y+y, 1.0f);
						
						glVertex3f((float)(l), (float)(y+y), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(l), (float)(y+y+1), 1.0f);
					glEnd();
					//frintface
					glBegin(GL_QUADS);
						glColor3f(0.686,0.898,0.050);
						glVertex3f((float)r, (float)(y+y+1), 1.0f);
						
						glVertex3f((float)r, (float)(y+y+1), 2.0f);
						
						glVertex3f((float)(r), (float)(y+y), 2.0f);
						
						glVertex3f((float)(r), (float)(y+y), 1.0f);
					glEnd();
				}
			}else if (boundry[y][r]=='A'){ //this is car, actually
				glBegin(GL_QUADS);
					glColor3f(0.0f, 1.0f, 0.0f);
					glVertex3f((float)r, (float)y+y, 1.0f);
					
				    glVertex3f((float)r, (float)(y+y+1), 1.0f);
				    
				    glVertex3f((float)(l), (float)(y+y+1), 1.0f);
				    
				    glVertex3f((float)(l), (float)(y+y), 1.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.0f, 1.0f, 0.0f);
					glVertex3f((float)r, (float)y+y, 1.0f);
					
				    glVertex3f((float)r, (float)(y+y), 2.0f);
				    
				    glVertex3f((float)(l), (float)(y+y), 2.0f);
				    
				    glVertex3f((float)(l), (float)(y+y), 1.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.0f, 1.0f, 0.0f);
					glVertex3f((float)r, (float)y+y, 2.0f);
					
				    glVertex3f((float)r, (float)(y+y+1), 2.0f);
				    
				    glVertex3f((float)(l), (float)(y+y+1), 2.0f);
				    
				    glVertex3f((float)(l), (float)(y+y), 2.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.0f, 1.0f, 0.0f);
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
				    glVertex3f((float)r, (float)(y+y+1), 2.0f);
				    
				    glVertex3f((float)(l), (float)(y+y+1), 2.0f);
				    
				    glVertex3f((float)(l), (float)(y+y+1), 1.0f);
				glEnd();
				//backface
				glBegin(GL_QUADS);
					glColor3f((188/255), (61/255), (26/255));
					glVertex3f((float)(l), (float)y+y, 1.0f);
					
				    glVertex3f((float)(l), (float)(y+y), 2.0f);
				    
				    glVertex3f((float)(l), (float)(y+y+1), 2.0f);
				    
				    glVertex3f((float)(l), (float)(y+y+1), 1.0f);
				glEnd();
				//frintface
				glBegin(GL_QUADS);
					glColor3f(0.0f, 1.0f, 0.0f);
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
				    glVertex3f((float)r, (float)(y+y+1), 2.0f);
				    
				    glVertex3f((float)(r), (float)(y+y), 2.0f);
				    
				    glVertex3f((float)(r), (float)(y+y), 1.0f);
				glEnd();
			}
			else if(boundry[y][r]=='#'){
				//create yellow car box
				//cout<<"true";
				glBegin(GL_QUADS);
					glColor3f((float)160/255,(float)70/255, (float)7/255);
					glVertex3f((float)r, (float)y+y, 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
					glVertex3f((float)(l), (float)(y+y+1), 1.0f);
					
					glVertex3f((float)(l), (float)(y+y), 1.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f((float)160/255,(float)70/255, (float)7/255);
					glVertex3f((float)r, (float)y+y, 1.0f);
					
					glVertex3f((float)r, (float)(y+y), 2.0f);
					
					glVertex3f((float)(l), (float)(y+y), 2.0f);
					
					glVertex3f((float)(l), (float)(y+y), 1.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f((float)160/255,(float)70/255, (float)7/255);
					glVertex3f((float)r, (float)y+y, 2.0f);
					
					glVertex3f((float)r, (float)(y+y+1), 2.0f);
					
					glVertex3f((float)(l), (float)(y+y+1), 2.0f);
					
					glVertex3f((float)(l), (float)(y+y), 2.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f((float)160/255,(float)70/255, (float)7/255);
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1), 2.0f);
					
					glVertex3f((float)(l), (float)(y+y+1), 2.0f);
					
					glVertex3f((float)(l), (float)(y+y+1), 1.0f);
				glEnd();
				//backface
				glBegin(GL_QUADS);
					glColor3f((188/255), (61/255), (26/255));
					glVertex3f((float)(l), (float)y+y, 1.0f);
					
					glVertex3f((float)(l), (float)(y+y), 2.0f);
					
					glVertex3f((float)(l), (float)(y+y+1), 2.0f);
					
					glVertex3f((float)(l), (float)(y+y+1), 1.0f);
				glEnd();
				//frintface
				glBegin(GL_QUADS);
					glColor3f((float)160/255,(float)70/255, (float)7/255);
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1), 2.0f);
					
					glVertex3f((float)(r), (float)(y+y), 2.0f);
					
					glVertex3f((float)(r), (float)(y+y), 1.0f);
				glEnd();

			}
				else if(boundry[y][r]=='B'){
				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.5f, 1.0f);
					glVertex3f((float)r, (float)y+y, 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
					glVertex3f((float)(l), (float)(y+y+1), 1.0f);
						glVertex3f((float)(l), (float)(y+y), 1.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.5f, 1.0f);
					glVertex3f((float)r, (float)y+y, 0.5f);
					
					glVertex3f((float)r, (float)(y+y+1), 0.5f);
					
					glVertex3f((float)(l), (float)(y+y+1), 0.5f);
						glVertex3f((float)(l), (float)(y+y), 0.5f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.5f, 1.0f);
					glVertex3f((float)r, (float)y+y, 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
					glVertex3f((float)(l), (float)(y+y+1), 1.0f);
						glVertex3f((float)(l), (float)(y+y), 1.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.5f, 1.0f);
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1), 0.5f);
					
					glVertex3f((float)(l), (float)(y+y+1), 0.5f);
						glVertex3f((float)(l), (float)(y+y+1), 1.0f);
				glEnd();
				//backface
				glBegin(GL_QUADS);
					glColor3f((188/255), (61/255), (26/255));
					glVertex3f((float)(l), (float)y+y, 1.0f);
					
					glVertex3f((float)(l), (float)(y+y), 0.5f);
					
					glVertex3f((float)(l), (float)(y+y+1), 0.5f);
						glVertex3f((float)(l), (float)(y+y+1), 1.0f);
				glEnd();
				//frintface
				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.5f, 1.0f);
					glVertex3f((float)r, (float)(y+y+1), 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1), 0.5f);
					
					glVertex3f((float)(r), (float)(y+y), 0.5f);
						glVertex3f((float)(r), (float)(y+y), 1.0f);
				glEnd();


			} else if(boundry[y][r]=='T'){
				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.0f, 0.7f);
					glVertex3f((float)r, (float)y+y-0.2f, 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1+0.2f), 1.0f);
					
					glVertex3f((float)(l), (float)(y+y+1+0.2f), 1.0f);
					
					glVertex3f((float)(l), (float)(y+y)-0.2f, 1.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.0f, 0.7f);
					glVertex3f((float)r, (float)y+y-0.2f, 3.0f);
					
					glVertex3f((float)r, (float)(y+y+1+0.2f), 3.0f);
					
					glVertex3f((float)(l), (float)(y+y+1+0.2f), 3.0f);
					
					glVertex3f((float)(l), (float)(y+y)-0.2f, 3.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.0f, 0.7f);
					glVertex3f((float)r, (float)y+y-0.2f, 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1+0.2f), 1.0f);
					
					glVertex3f((float)(l), (float)(y+y+1+0.2f), 1.0f);
					
					glVertex3f((float)(l), (float)(y+y)-0.2f, 1.0f);
				glEnd();

				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.0f, 0.7f);
					glVertex3f((float)r, (float)(y+y+1+0.2f), 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1+0.2f), 3.0f);
					
					glVertex3f((float)(l), (float)(y+y+1+0.2f), 3.0f);
					
					glVertex3f((float)(l), (float)(y+y+1+0.2f), 1.0f);
				glEnd();
				//backface
				glBegin(GL_QUADS);
					glColor3f((188/255), (61/255), (26/255));
					glVertex3f((float)(l), (float)y+y-0.2f, 1.0f);
					
					glVertex3f((float)(l), (float)(y+y)-0.2f, 3.0f);
					
					glVertex3f((float)(l), (float)(y+y+1+0.2f), 3.0f);
					
					glVertex3f((float)(l), (float)(y+y+1+0.2f), 1.0f);
				glEnd();
				//frintface
				glBegin(GL_QUADS);
					glColor3f(0.5f, 0.0f, 0.7f);
					glVertex3f((float)r, (float)(y+y+1+0.2f), 1.0f);
					
					glVertex3f((float)r, (float)(y+y+1+0.2f), 3.0f);
					
					glVertex3f((float)(r), (float)(y+y)-0.2f, 3.0f);
					
					glVertex3f((float)(r), (float)(y+y)-0.2f, 1.0f);
				glEnd();
			}

		}
	}
	//////////////////////////////////////////////////////
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	readConfig("config.ini");
	boundry = getBoundry(control.Road_Width,control.Road_Length);
	
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
	/* get a 640 x 480 window */
	glutInitWindowSize(640, 480);  
	glutInitWindowPosition(0, 0);  
	
	////CREATING SIMULATION ID////
	string id = control.Road_Id;
	char h[100] = "Traffic Road Simulation ";
	for(int q=0;q<(sizeof(control.Road_Id)/sizeof(*(control.Road_Id)));q++){
		h[24+q] = control.Road_Id[q];
	}
	window = glutCreateWindow(h);
	//////////////////////////////
	
	glutDisplayFunc(&DrawGLScene);
	glutIdleFunc(&DrawGLScene);
	
	/* Register the function called when our window is resized. */
	glutReshapeFunc(&ReSizeGLScene);
	
	/* Initialize our window. */
	InitGL(800, 600); 

	/* Start Event Processing Engine */  
	glutMainLoop();
	return 0;
}