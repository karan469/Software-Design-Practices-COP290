#ifndef TAKEFILTERS_H
#define TAKEFILTERS_H

#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <fstream>
#include <sstream>
#define Vector_Matrix_Float vector<vector<float>>
#define Vector_Tetris_Float vector<vector<vector<float>>>
#define Vector_Quadris_Float vector<vector<vector<vector<float>>>>
using namespace std;

struct filterAndBias {
    Vector_Tetris_Float filter;
    Vector_Matrix_Float bias;
};
struct filterAndBias4d {
    Vector_Quadris_Float filter;
    Vector_Matrix_Float bias;
};
struct filterAndBias filterBias(string File,int n,int m,int k){ // argv[m] contains matrix.txt // argv[n] contains now of rows
    // N = filter size
    // K = DepthFilter
    // M = bias
    fstream infile;
    infile.open(File);
    if(!infile.is_open()){
        cout << "File given is not correct"<<endl;
    }
    string line ="";
    Vector_Tetris_Float v2(k, Vector_Matrix_Float(n,vector<float>(n,0.0f)));
    Vector_Matrix_Float v1(m,vector<float>(1,0.0f));
    struct filterAndBias data;
    float p;
    for(int l = 0; l < k; l++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++)
            {
                getline(infile, line);
                if(line != "")
                {
                    stringstream num(line);
                    num >> p;
                    v2[l][j][i]= (float)p;//Column major
                }
            }    
        }
    }
    for(int i=0 ; i<m; i++)
    {
        getline(infile, line);
        if(line != "")
        {
            stringstream num(line);
            num >> p;
            v1[i][0] = (float)p;
        } 
    }
    data.filter = v2;
    data.bias = v1;
    //free((void*)p);
    return data;
}

struct filterAndBias4d filterBias4d(string File,int a,int n,int m,int k){ // argv[m] contains matrix.txt // argv[n] contains now of rows
    // N = filter size
    // K = HeightFilter
    // M = bias
    // a = no of filter
    fstream infile;
        infile.open(File);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
        }
    string line ="";
    Vector_Quadris_Float v2(a,Vector_Tetris_Float(k,Vector_Matrix_Float(n,vector<float>(n,0.0f))));
    Vector_Matrix_Float v1(m,vector<float>(1,0.0f));
    struct filterAndBias4d data;
    float p;
    for(int nooffilter = 0; nooffilter < a; nooffilter++){
        for(int l = 0; l < k; l++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++)
                {
                    getline(infile, line);
                    if(line != "")
                    {
                        stringstream num(line);
                        num >> p;
                        v2[nooffilter][l][j][i] = (float)p;//column major
                    }
                }    
            }
        }
    }
    for(int i=0 ; i<m; i++)
    {
        getline(infile, line);
        if(line != "")
        {
            stringstream num(line);
            num >> p;
            v1[i][0] = (float)p;
        } 
    }
    data.filter = v2;
    data.bias = v1;
    return data;
}

#endif