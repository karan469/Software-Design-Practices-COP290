#ifndef PRINTHEAD_H
#define PRINTHEAD_H

#include <algorithm>
#include <vector>
#define Vector_Matrix vector<vector<int>>
#define float_Vector vector<float>
#define Vector_Matrix_Float vector<vector<float>>
using namespace std;

void print(Vector_Matrix v){
    for(int i=0;i<v.size();i++){
      for(int j=0;j<v[0].size();j++){
          cout<<v[i][j]<<" ";
          
      }
      cout<<endl;
  }
}
void print(float_Vector v){
    for(int i=0;i<v.size();i++){
      cout<<v[i]<<" ";
  }
}
void print(Vector_Matrix_Float v){
    for(int i=0;i<v.size();i++){
      for(int j=0;j<v[0].size();j++){
          cout<<v[i][j]<<" ";
          
      }
      cout<<endl;
  }
}
#endif
