#include <iostream>
#include <algorithm>
#include <vector>
#include "convolution.h"
#define Vector_Matrix vector<vector<int>>
using namespace std;



int main()
{
  //int kernel = {{1,2},{2,3},{3,4}};
  Vector_Matrix v2{{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6}};
  Vector_Matrix kernel{{1,2,3},{1,2,3},{1,2,3}};
  //vector<vector<int>> v3{{3,4,5},{3,4,5},{3,4,5}};
  Vector_Matrix padded_image;
  padded_image = convolution_pad(v2,1);
  print(convolution_matrixmult(kernel,padded_image));

  cout<<endl;

  print(convolution(kernel,padded_image));
  //cout<<sub_convo(v1,v2);
    
  return 0;
}
