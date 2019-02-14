//To Be Done: Error handling if rows%stride!=0

#ifndef POOLING_H
#define POOLING_H
#include <algorithm>
#include <vector>
#define Vector_Matrix_Float vector<vector<float>>
using namespace std;

// max pooling and average pooling are on the same program
//      max pooling = 'max'   average pooling = 'avg'
// assuming square matrix according to the problem statement

//max pooling function
Vector_Matrix_Float Pooling(Vector_Matrix_Float v1, string pool,int stride)
{
    int size = v1.size();
    int n = (int)((float)size/(float)stride);
    string max = "max";
    string avg = "avg";
    // This contains the answer
    Vector_Matrix_Float ans(n,vector<float>((n),0));
    // This contains Part to check
    Vector_Matrix_Float part(n,vector<float>(n,0));

    
    for(int i = 0; i < size; i+=stride){
        for(int j = 0; j < size; j+=stride){
            if (pool == max) {
                int max = (int)(-1*2147483648);
                for(int l = 0; l < stride; l++){
                    for(int m = 0; m < stride; m++){
                        if(i+l<size && j+m<size){
                            if(max < v1[i+l][j+m]){
                                int temp = max;
                                max = v1[i+l][j+m];
                            }
                        }
                    }  
                }
                ans[i/stride][j/stride] = max;
            }  
            else if (pool == avg) {
                int avg = 0;
                for(int l = 0; l < stride; l++){
                    for(int m = 0; m < stride; m++){
                        if(i+l<size && j+m<size){
                            avg+=v1[i+l][j+m];
                        }
                    }  
                }
                ans[i/stride][j/stride] = avg/(stride*stride);
            }  
            else 
            {
                cout << "choose 'max' or 'avg' pool" << endl; 
                return ans;
            }   
        }
        
    }
    return ans;
}

#endif
