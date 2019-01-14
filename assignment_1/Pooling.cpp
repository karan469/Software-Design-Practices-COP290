#include <iostream>
#include <algorithm>
#include <vector>
#define Vector_Matrix vector<vector<int>>
using namespace std;
#include "Pooling.h"
#include "printHead.h"

// max pooling and average pooling are on the same program
//      max pooling = 'max'   average pooling = 'avg'
// assuming square matrix according to the problem statement

// Vector_Matrix advancePadding(Vector_Matrix v, int stride){
//     int rows = v.size();
//     int coloumn
// }

//max pooling function
// Vector_Matrix Pooling(Vector_Matrix v1, string pool,int stride)
// {
//     int size = v1.size();
//     int n = size/stride;
//     string max = "max";
//     string avg = "avg";
//     // This contains the answer
//     Vector_Matrix ans(n,vector<int>((n),0));
//     // This contains Part to check
//     Vector_Matrix part(n,vector<int>(n,0));

    
//     for(int i = 0; i < size; i+=stride){
//         for(int j = 0; j < size; j+=stride){
//             if (pool == max) {
//                 int max = 0;
//                 for(int l = 0; l < stride; l++){
//                     for(int m = 0; m < stride; m++){
//                         if(max < v1[i+l][j+m]){
//                             max = v1[i+l][j+m];
//                         }
//                     }  
//                 }
//                 ans[i/stride][j/stride] = max;
//             }  
//             else if (pool == avg) {
//                 int avg = 0;
//                 for(int l = 0; l < stride; l++){
//                     for(int m = 0; m < stride; m++){
//                         avg+=v1[i+l][j+m];
//                     }  
//                 }
//                 ans[i/stride][j/stride] = avg/(stride*stride);
//             }  
//             else 
//             {
//                 cout << "choose 'max' or 'avg' pool" << endl; 
//                 return ans;
//             }   
//         }
        
//     }
//     return ans;
// }

int main(int argc, char const *argv[])
{
    Vector_Matrix v1{{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6}};
    print(Pooling(v1,"min",2));
    return 0;

}
