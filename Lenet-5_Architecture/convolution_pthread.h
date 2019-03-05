#ifndef CONVOLUTION_PTHREAD_H
#define CONVOLUTION_PTHREAD_H
#include <algorithm>
#include <vector>
#include <chrono>
#include "pthread.h"
// #include "/home/karan/intel/compilers_and_libraries_2019.1.144/linux/mkl/include/mkl.h"
using namespace std;
using namespace std::chrono;

#define Vector_Matrix vector<vector<int>>
#define Vector_Matrix_Float vector<vector<float>>

#include <pthread.h>
#include <chrono>
using namespace std::chrono;
using namespace std; 
#define MAX_THREAD 4
#define MAX 23100
struct maxisize{int maxi;};

struct maxisize t1 = {23100};

Vector_Matrix_Float matA; 
vector<float> matB; 
vector<float> matC;
int step_i = 0;

void* multi(void* arg){ 
    int core = step_i++; 
  
    // Each thread computes 1/4th of matrix multiplication 
    for (int i = core * t1.maxi / 4; i < (core + 1) * t1.maxi / 4; i++)  
            for (int k = 0; k < t1.maxi; k++)  
                matC[i] += matA[i][k] * matB[k]; 
}
void mult_using_pthread(Vector_Matrix_Float matA, vector<float> matB){
    //int matC[m][k];
    pthread_t threads[MAX_THREAD]; 
  
    // Creating four threads, each evaluating its own part 
    for (int i = 0; i < MAX_THREAD; i++) { 
        int* p; 
        pthread_create(&threads[i], NULL, multi, (void*)(p)); 
    } 
  
    // joining and waiting for all threads to complete 
    for (int i = 0; i < MAX_THREAD; i++)  
        pthread_join(threads[i], NULL);     
  
    // Displaying the result matrix 
    // cout << endl 
    //      << "Multiplication of A and B" << endl; 
    // for (int i = 0; i < t1.maxi; i++) { 
    //     cout << matC[i][0] << " ";         
    //     cout << endl; 
    // }
}
float time_pthread(Vector_Matrix_Float matA, vector<float> matB){
    auto start1 = high_resolution_clock::now();
    mult_using_pthread(matA, matB);
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1-start1);
    return (float)duration.count();
}


// float sub_convo(Vector_Matrix_Float v1, Vector_Matrix_Float v2){
//     float sum = 0;
//     int n = v1[0].size();
//     for(int i = 0;i<n;i++){
//         for(int j=0;j<n;j++){
//             sum += v1[i][j]*v2[n-i-1][n-j-1];
//         }
//     }
//     return sum;
// }

Vector_Matrix_Float convolution_matrixmult_pthread(Vector_Matrix_Float v1, Vector_Matrix_Float v2){
    // v1: kernel
    
    int rows_v1 = v1.size();
    int rows_v2 = v2.size();
    int coloumns_v1 = v1[0].size();
    int coloumns_v2 = v2[0].size();
    int n = rows_v1;
    
    Vector_Matrix_Float v((rows_v2-rows_v1+1),vector<float>((coloumns_v2-coloumns_v1+1),0.0f)); //answer here
    Vector_Matrix_Float v_temp(n,vector<float>(n,0.0f)); //Extraction of smaller matrix from image 
    int columns_con_matmul= (coloumns_v2-coloumns_v1+1);//Columns of answer matrix
    int rows_con_matmul = (rows_v2-rows_v1+1);//rows of answer matrix
    int col_row=columns_con_matmul*rows_con_matmul;//total elements
    //col_row will become rows in con_matmul

    Vector_Matrix_Float con_matmul(col_row, vector<float>(rows_v1*coloumns_v1,0.0f));
    //contains vectors that is to be multiplied with kernel
    int x_1=0,y_1=0;
    for(int x=0;x<(rows_v2-rows_v1+1);x++){
        for(int y=0;y<(coloumns_v2-coloumns_v1+1);y++){
            for(int a=0;a<rows_v1;a++){
                for(int b=0;b<coloumns_v1;b++){
                    con_matmul[x_1][y_1] = v2[a+x][b+y];
                    y_1++;
                }
            }
            y_1 = 0;
            x_1++;
        }
    }
    //Making kernel linear
    int no_of_ele = rows_v1*coloumns_v1;
    vector<float> v_templ(no_of_ele,0);
    int count = 0;
    for(int i = 0; i < rows_v1; i++)
    {
        for(int j = 0; j < coloumns_v1; j++)
        {
            v_templ[count] = v1[rows_v1-i-1][coloumns_v1-j-1];
            count ++;
        } 
    }
    
    //Matrix multiplication //con_matmul: col_row X rows_v1*coloumns_v1
                            //v_templ: rows_v1 X coloumns_v1
    vector<float> sum(col_row,0);
    if(no_of_ele == v_templ.size())
    {
        for(int h=0;h<col_row;h++){
            for(int qwe=0;qwe<(rows_v1*coloumns_v1);qwe++){
                matA[h][qwe] = con_matmul[h][qwe];
            }
        }
        for(int ew=0;ew<rows_v1;ew++){
            matB[ew] = v_templ[ew];
        }
        for (int i = 0; i < col_row; ++i)
        {
            mult_using_pthread(matA, matB);
            sum[i] = matC[i];
        }

    }
    count = 0;
    for(int i = 0; i < rows_con_matmul; i++)
    {
        for(int j = 0; j < columns_con_matmul; j++)
        {
            v[i][j] = sum[count];
            count++;
        }
        
    }
    
    //print(v);
    return v;    
}

#endif