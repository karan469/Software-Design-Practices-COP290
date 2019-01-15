#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#define float_Vector vector<float>
#define forLoop for(int i=0;i<v.size();i++)
using namespace std;


void print(float_Vector v){
    for(int i=0;i<v.size();i++){
      cout<<v[i]<<" ";
  }
}
// void print_sum(float_Vector v){
//     float ans = 0.0;
//     for(int i=0;i<v.size();i++){
//         ans += v[i];
//     }
//     cout<<"***"<<ans<<"***";
// }
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
// int main()
// {
//   mt19937 mt(1729); //comes from #include <random>: New method for random number generation with much more distributed numbers
//   uniform_int_distribution<int> dist(0,20); //comes from #include <random>
//   float_Vector v(10);
//   for(int i=0;i<10;i++){
//       //cout<<dist(mt)<<" ";
//       v[i] = (float)(dist(mt)/3);
//   }
//   print(softmax(v));
//   //cout<<endl;
//   //print_sum(softmax(v));
    
//   return 0;
// }
