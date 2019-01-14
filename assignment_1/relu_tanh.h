//To be done: Incorporate it into the main file
#ifndef RELU_TANH_H
#define RELU_TANH_H

#include <algorithm>
#include <vector>
#define Vector_Matrix vector<vector<int>>
#define float_Vector vector<float>
#define Vector_Matrix_Float vector<vector<float>>
using namespace std;

float makeRelu(float a){
    if(a<=0){
        return 0;
    }
    return a;
}
float makeTanh(float a){
    float expo = exp(2*a);
    return (float)((expo-1)/(expo+1));
}
Vector_Matrix_Float reluMatrix(Vector_Matrix_Float v){
    int rows = v.size();
    int coloumns = v[0].size();
    Vector_Matrix_Float ans(rows,vector<float>(coloumns,0.0));
    for(int i=0;i<rows;i++){
        for(int j=0;j<coloumns;j++){
            ans[i][j] = makeRelu((float)v[i][j]);
        }
    }
    return ans;
}

Vector_Matrix_Float tanhMatrix(Vector_Matrix_Float v){
    Vector_Matrix_Float ans(v.size(),vector<float>(v[0].size(),0.0));
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[0].size();j++){
            ans[i][j] = makeTanh((float)v[i][j]);
        }
    }
    return ans;
}
Vector_Matrix_Float randomVectorMatrixGenerator(int m, int n){
    Vector_Matrix_Float v(m,vector<float>(n,0));
    // mt19937 mt(1729); //comes from #include <random>: New method for random number generation with much more distributed numbers
    // uniform_int_distribution<int> dist(0,40);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            //v[i][j] = (float)(dist(mt)/3);
        
            v[i][j] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*10;
        }
    }
    return v;
}

#endif