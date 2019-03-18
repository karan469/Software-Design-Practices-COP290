#include <iostream> 
#include <bits/stdc++.h> 
#include <regex> 
#include<string.h> 
#include <fstream>
#include <sstream>

using namespace std;

struct vehicle{
    string type;
    float maxspeed;
    float acc;
    float length;
    float width;
};
struct road{
    float id;
    float length;
    float width;
    float signal;
};
class Instr{
    public:
    string instr;
    string signal; //for Signal RED or GREEN
    int time;//for Pass instr
    // instruction strings are:
    // 1. insertVehicle
    // 2. Pass
    // 3. START and END
    struct Instr *next;
};

struct vehicle car;
struct vehicle bike;
struct vehicle truck;
struct vehicle bus;
vector<string> Instrs(1024,"");
Instr *startin = new Instr; 
Instr *Lastin = startin;
struct road roadspec;
float defmaxspeed;
float defacc;

void nextline(string filename)
{
    regex sim("[a-zA-Z_]+[' ']*[a-zA-z0-9]*");
    regex simmatch("([a-zA-Z_]+)([' ']*)([a-zA-z0-9]*)([' ']*)(#*.*)");
    smatch simm;

    fstream infile;
    infile.open(filename);
    string line ="";
    int count = 0; 
    if (infile.is_open())
    {   
        while(getline(infile,line)){    
            if (regex_match(line,simmatch))
            {
                regex_match(line,simm,sim);
                string p = "";
                int c = 0;
                p = simm.str();
                if (p=="START") {
                    while(getline(infile,line)){
                        // Instr *lastin = NULL;
                        // lastin=new Instr;
                        // if (c==0){startin = lastin;}
                        regex_search(line,simm,sim);
                        p = simm.str();
                        if (p.substr(0,6)=="Signal") {
                            // lastin->instr = p.substr(0,6);
                            // lastin->signal = p.substr(7);
                            // Lastin = lastin;
                            // cout<<"eles"<<lastin->instr<<" "<<lastin->signal<<" "<<lastin->time<< endl;
                            // Lastin = Lastin->next;
                            Instrs[count] = p;
                            count++;
                            // Lastin = new Instr;
                        }
                        else if (p.substr(0,3)=="Car")
                        {
                            // lastin->instr = p.substr(0,3);
                            // lastin->signal = p.substr(4);
                            // Lastin = lastin;
                            // cout<<"eles"<<lastin->instr<<" "<<lastin->signal<<" "<<lastin->time<< endl;
                            // Lastin = Lastin->next;
                            Instrs[count] = p;
                            count++;
                            // Lastin = new Instr;
                        }
                        else if (p.substr(0,4)=="bike")
                        {
                            // lastin->instr = p.substr(0,4);
                            // lastin->signal = p.substr(5);
                            // Lastin = lastin;
                            // cout<<"eles"<<lastin->instr<<" "<<lastin->signal<<" "<<lastin->time<< endl;
                            // Lastin = Lastin->next;
                            Instrs[count] = p;
                            count++;
                            // Lastin = new Instr;
                        }
                        else if (p.substr(0,3)=="Bus")
                        {
                            // lastin->instr = p.substr(0,3);
                            // lastin->signal = p.substr(4);
                            // Lastin = lastin;
                            // cout<<"eles"<<lastin->instr<<" "<<lastin->signal<<" "<<lastin->time<< endl;
                            // Lastin = Lastin->next;
                            Instrs[count] = p;
                            count++;
                            // Lastin = new Instr;
                        }
                        else if (p.substr(0,5)=="Truck")
                        {
                            // lastin->instr = p.substr(0,5);
                            // lastin->signal = p.substr(6);
                            // Lastin = lastin;
                            // cout<<"eles"<<lastin->instr<<" "<<lastin->signal<<" "<<lastin->time<< endl;
                            // Lastin = Lastin->next;
                            Instrs[count] = p;
                            count++;
                            // Lastin = new Instr;
                        }
                        else if (p.substr(0,4)=="Pass")
                        {
                        //     lastin->instr = p.substr(0,4);
                        //     lastin->time = stof(p.substr(5));
                        //     Lastin = lastin;
                        //     cout<<"eles"<<lastin->instr<<" "<<lastin->signal<<" "<<lastin->time<< endl;
                        //     Lastin = Lastin->next;
                            Instrs[count] = p;
                            count++;
                            // Lastin = new Instr;
                        }
                        else if (p=="END")
                        {
                            Instrs[count] = p;
                            count++;
                            break;                                
                        }
                    }
                }
            }
        }
    }
}
void readini(string filename){
    regex expr("[a-zA-Z_]+[' ']*[=][' ']*[a-zA-Z0-9]+"); //for '='
    regex sim("[a-zA-Z_]+[' ']*[a-zA-z0-9]*");
    regex reget("(#)(.*)");
    regex exprmatch("[a-zA-Z_]+[' ']*[=][' ']*[a-zA-Z0-9]+[' ']*(#*.*)");
    regex simmatch("([a-zA-Z_]+)([' ']*)([a-zA-z0-9]*)([' ']*)(#*.*)");
    smatch exprm;
    smatch simm;

    
    fstream infile;
    infile.open(filename);
    string line ="";
    if (infile.is_open())
    {
        while ( getline(infile,line) )
        {
            if(!regex_match(line,reget))
            {
                if(regex_match(line,exprmatch))
                {
                    regex_search(line,exprm,expr);
                    string p = "";
                    p = exprm.str();//gives expresssion in file
                    if(p.substr(0,12)=="Vehicle_Type")
                    {
                        struct vehicle lastveh;
                        lastveh.type=p.substr(15);
                        getline(infile,line);
                        regex_search(line,exprm,expr);
                        p = exprm.str();
                        lastveh.length=stof(p.substr(17));

                        getline(infile,line);
                        regex_search(line,exprm,expr);
                        p = exprm.str();
                        lastveh.width=stof(p.substr(16));
                        
                        getline(infile,line);
                        if(line==""){
                            lastveh.acc=defacc;
                            lastveh.maxspeed=defmaxspeed;
                        }
                        else
                        {
                            regex_search(line,exprm,expr);
                            p = exprm.str();
                            if(p.substr(0,16)=="Vehicle_MaxSpeed")
                            {
                                lastveh.maxspeed=stof(p.substr(19));
                                getline(infile,line);
                                if(line=="")
                                {
                                    lastveh.acc=defacc;
                                }
                                else
                                {
                                    regex_search(line,exprm,expr);
                                    p = exprm.str();
                                    lastveh.acc=stof(p.substr(23));
                                }
                            }
                            else
                            {
                                lastveh.acc=stof(p.substr(23));
                                getline(infile,line);
                                if(line=="")
                                {
                                    lastveh.maxspeed=defmaxspeed;
                                }
                                else
                                {
                                    regex_search(line,exprm,expr);
                                    p = exprm.str();
                                    lastveh.maxspeed=stof(p.substr(19));
                                }
                            }
                        } 
                        if(lastveh.type == "Car")
                        {
                            car = lastveh;
                        }   
                        else if (lastveh.type == "bike")
                        {
                            bike = lastveh;
                        }
                        else if (lastveh.type == "Bus")
                        {
                            bus = lastveh;
                        }
                        else if (lastveh.type == "Truck")
                        {
                            truck = lastveh;
                        }                         
                    }
                    else if (p.substr(0,4)=="Road")
                    {
                        roadspec.id=stof(p.substr(10));

                        getline(infile,line);
                        regex_search(line,exprm,expr);
                        p = exprm.str();
                        roadspec.length=stof(p.substr(14));

                        getline(infile,line);
                        regex_search(line,exprm,expr);
                        p = exprm.str();
                        roadspec.width=stof(p.substr(13));

                        getline(infile,line);
                        regex_search(line,exprm,expr);
                        p = exprm.str();
                        roadspec.signal=stof(p.substr(14));
                    }
                    else if (p.substr(0,7)=="Default")
                    {
                        defmaxspeed = stof(p.substr(19));
                        getline(infile,line);
                        regex_search(line,exprm,expr);
                        p = exprm.str();
                        defacc=stof(p.substr(23));
                    } 
                    else
                    {
                        cout << "wrong parameters" << endl;
                    }
                       
                }
            }
            else
            {
                // cout << "matched"<<endl;
            }
            
        }
        infile.close();
    }
    else
    {
        cout << "File given is not correct"<<endl;
    }
    
}

int main(int argc, char const *argv[])
{
    readini("./config.ini");
    cout << car.type << car.acc << car.maxspeed << car.length << car.width<<endl;
    cout << bike.type << bike.acc << bike.maxspeed << bike.length << bike.width<<endl;
    cout << truck.type << truck.acc << truck.maxspeed << truck.length << truck.width<<endl;
    cout << bus.type << bus.acc << bus.maxspeed << bus.length << bus.width<<endl;

    nextline("./config.ini");
    for(int i = 0; i < 1024; i++)
    {
        cout << Instrs[i]<<endl;
    }
    
    return 0;
}



