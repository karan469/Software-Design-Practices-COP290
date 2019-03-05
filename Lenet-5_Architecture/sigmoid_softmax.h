#ifndef SIGMOID_SOFTMAX_H
#define SIGMOID_SOFTMAX_H

#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#define float_Vector vector<float>
#define forLoop for(int i=0;i<v.size();i++)
using namespace std;


void print_sum(float_Vector v){
    float ans = 0.0;
    for(int i=0;i<v.size();i++){
        ans += v[i];
    }
    cout<<"***"<<ans<<"***";
}
float_Vector sigmoid(float_Vector a){
    float_Vector ans(a.size(),0.0);
    for(int i=0;i<a.size();i++){
        ans[i] = 1/(1+exp(-1*a[i]));
    }
    return ans;
}
float_Vector softmax(float_Vector a){
    float_Vector blu(a.size(),0.0);
    float sum = 0.0;
    for(int i=0;i<a.size();i++){
        sum += exp(a[i]);
    }
    //cout<<"AAA "<<sum<<" ";
    for(int j=0;j<a.size();j++){
        blu[j] = (exp(a[j]))/sum;
    }
    return blu;
}

#endif