#ifndef CONVOLUTION_MkL_H
#define CONVOLUTION_MkL_H
#include <algorithm>
#include <vector>
#include <chrono>

// PATH TO MKL
#include "/home/karan/intel/compilers_and_libraries_2019.1.144/linux/mkl/include/mkl.h"
using namespace std;
using namespace std::chrono;

#define Vector_Matrix vector<vector<int>>
#define Vector_Matrix_Float vector<vector<float>>

void matrix_multiplcation_Intelmkl(double *A, int A_width, int A_height,double *B, int B_width, int B_height, double *C)
{
    double alpha, beta;
    int lda, incx, incy, i;
    int m = A_height;
    int n = 1; 
    int k = A_width;
    lda = A_height;  

    incx = 1;
    incy = 1;
    alpha = 1;
    beta = 0;


    //cout<<"Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface\n\n";
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,m,n,k,alpha,A,k,B,n,beta,C,n);
	//cout<<"Computation completed.\n\n";
}

Vector_Matrix_Float convolution_matrixmult_mkl(Vector_Matrix_Float v1, Vector_Matrix_Float v2,string libToUse){
    // v1: kernel
    
    long int rows_v1 = v1.size();
    long int rows_v2 = v2.size();
    long int coloumns_v1 = v1[0].size();
    long int coloumns_v2 = v2[0].size();
    long int n = rows_v1;
    
    Vector_Matrix_Float v((rows_v2-rows_v1+1),vector<float>((coloumns_v2-coloumns_v1+1),0.0f)); //answer here
    Vector_Matrix_Float v_temp(n,vector<float>(n,0.0f)); //Extraction of smaller matrix from image 
    long int columns_con_matmul= (coloumns_v2-coloumns_v1+1);//Columns of answer matrix
    long int rows_con_matmul = (rows_v2-rows_v1+1);//rows of answer matrix
    long int col_row=columns_con_matmul*rows_con_matmul;//total elements
    //col_row will become rows in con_matmul

    Vector_Matrix_Float con_matmul(col_row, vector<float>(rows_v1*coloumns_v1,0.0f));
    //contains vectors that is to be multiplied with kernel
    long int x_1=0,y_1=0;
    for(long int x=0;x<(rows_v2-rows_v1+1);x++){
        for(long int y=0;y<(coloumns_v2-coloumns_v1+1);y++){
            for(long int a=0;a<rows_v1;a++){
                for(long int b=0;b<coloumns_v1;b++){
                    con_matmul[x_1][y_1] = v2[a+x][b+y];
                    y_1++;
                }
            }
            y_1 = 0;
            x_1++;
        }
    }
    //Making kernel linear
    long int no_of_ele = rows_v1*coloumns_v1;
    vector<float> v_templ(no_of_ele,0);
    long int count = 0;
    //making kernel linear and flipping also
    for(long int i = 0; i < rows_v1; i++)
    {
        for(long int j = 0; j < coloumns_v1; j++)
        {
            v_templ[count] = v1[rows_v1-i-1][coloumns_v1-j-1];
            count ++;
        } 
    }

    if(libToUse == "intelmkl")
    {
        long int m = col_row;
        long int k = no_of_ele;
        long int n = 1;
        long int sizeofa = m * k;
        long int sizeofb = k * n;
        long int sizeofc = m * n;
        double* A = (double*)malloc(sizeof(double) * sizeofa);
        double* B = (double*)malloc(sizeof(double) * sizeofb);
        double* C = (double*)malloc(sizeof(double) * sizeofc);

        count = 0;
        for(long int i = 0; i < m; i++)
        {
            for(long int j = 0; j < k; j++)
            {
                A[count] = con_matmul[i][j];
                count++;
            }
            
        }

        for(long int i = 0; i < k; i++)
        {
            B[i] = v_templ[i];
            // cout << B[i] << " ";
        }
        for(long int i = 0; i < m*n; i++)
        {
            C[i] = 0;
        }
        auto start1 = high_resolution_clock::now();

        matrix_multiplcation_Intelmkl(A,k,m,B,1,k,C);

        // auto stop1 = high_resolution_clock::now();
        // auto duration = duration_cast<microseconds>(stop1-start1);
        // float time = (float)duration.count()/(float)1000000;
        // cout << "time: " << time << " seconds" << endl;
        count = 0;
        for(long int i = 0; i < rows_con_matmul; i++)
        {
            for(long int j = 0; j < columns_con_matmul; j++)
            {
                v[i][j] = C[count];
                count++;
            }
            
        }
        free(A);
        free(B);
        free(C);
    }
    else
    {
        //Matrix multiplication
        auto start1 = high_resolution_clock::now();
        // vector<float> sum(col_row,0);
        double* sum = (double*)malloc(sizeof(double) * col_row);
        if(no_of_ele == v_templ.size())
        {
            for(long int i = 0; i < col_row; i++)
            {
                for(long int j = 0; j < no_of_ele; j++)
                {
                    sum[i]+=con_matmul[i][j]*v_templ[j];
                }   
            }
        }
        // TESTING PeRFORMANCE wITH OpenBLAS
        // auto stop1 = high_resolution_clock::now();
        // auto duration = duration_cast<microseconds>(stop1-start1);
        // float time = (float)duration.count()/(float)1000000;
        // cout << "time: " << time << " seconds" << endl;
        // count = 0;
        // for(long int i = 0; i < rows_con_matmul; i++)
        // {
        //     for(long int j = 0; j < columns_con_matmul; j++)
        //     {
        //         v[i][j] = sum[count];
        //         count++;
        //     }
            
        // }
    }
    return v;    
}


#endif