#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#include "sigmoid_softmax.h"
#include "printHead.h"

using namespace std;

int main()
{
  mt19937 mt(1729); //comes from #include <random>: New method for random number generation with much more distributed numbers
  uniform_int_distribution<int> dist(0,20); //comes from #include <random>
  float_Vector v(10);
  for(int i=0;i<10;i++){
      //cout<<dist(mt)<<" ";
      v[i] = (float)(dist(mt)/3);
  }
  print(softmax(v));
    
  return 0;
}
