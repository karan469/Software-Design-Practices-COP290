#ifndef CONVOLUTION_H 
#define CONVOLUTION_H

#include <algorithm>
#include <vector>
#define Vector_Matrix_Float vector<vector<float>>
using namespace std;

int sub_convo(Vector_Matrix_Float v1, Vector_Matrix_Float v2){
    int sum = 0;
    int n = v1[0].size();
    for(int i = 0;i<n;i++){
        for(int j=0;j<n;j++){
            sum += v1[i][j]*v2[n-i-1][n-j-1];
        }
    }
    return sum;
}
//Harsh
Vector_Matrix_Float convolution_matrixmult(Vector_Matrix_Float v1, Vector_Matrix_Float v2){
    // v1: kernel
    
    int rows_v1 = v1.size();
    int rows_v2 = v2.size();
    int coloumns_v1 = v1[0].size();
    int coloumns_v2 = v2[0].size();
    int n = rows_v1;
    
    Vector_Matrix_Float v((rows_v2-rows_v1+1),vector<float>((coloumns_v2-coloumns_v1+1),0)); //answer here
    Vector_Matrix_Float v_temp(n,vector<float>(n,0)); //Extraction of smaller matrix from image 
    int columns_con_matmul= (coloumns_v2-coloumns_v1+1);//Columns of answer matrix
    int rows_con_matmul = (rows_v2-rows_v1+1);//rows of answer matrix
    int col_row=columns_con_matmul*rows_con_matmul;//total elements
    //col_row will become rows in con_matmul

    Vector_Matrix_Float con_matmul(col_row, vector<float>(rows_v1*coloumns_v1,0));
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
    }\
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
    
    //Matrix multiplication
    vector<float> sum(col_row,0);
    if(no_of_ele == v_templ.size())
    {
        for(int i = 0; i < col_row; i++)
        {
            for(int j = 0; j < no_of_ele; j++)
            {
                sum[i]+=con_matmul[i][j]*v_templ[j];
            }   
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

//Karan
Vector_Matrix_Float convolution(Vector_Matrix_Float v1, Vector_Matrix_Float v2){
    // v1: kernel
    
    int rows_v1 = v1.size();
    int rows_v2 = v2.size();
    int coloumns_v1 = v1[0].size();
    int coloumns_v2 = v2[0].size();
    int n = rows_v1;
    
    Vector_Matrix_Float v((rows_v2-rows_v1+1),vector<float>((coloumns_v2-coloumns_v1+1),0)); //answer here
    Vector_Matrix_Float v_temp(n,vector<float>(n,0)); //Extraction of smaller matrix from image matrix
    
    for(int x=0;x<(coloumns_v2-coloumns_v1+1);x++){
        for(int y=0;y<(rows_v2-rows_v1+1);y++){
            for(int a=0;a<coloumns_v1;a++){
                for(int b=0;b<rows_v1;b++){
                    v_temp[a][b] = v2[a+x][b+y];
                }
            }
            v[x][y] = sub_convo(v1,v_temp);
        }
    }
    //print(v);
    return v;    
}

Vector_Matrix_Float convolution_pad(Vector_Matrix_Float v2, int padding){
    Vector_Matrix_Float pad(v2.size()+2*padding,vector<float>(v2[0].size()+2*padding,0));
    for(int q=0;q<v2.size();q++){
        for(int w=0;w<v2[0].size();w++){
            pad[q+padding][w+padding] = v2[q][w];
        }
    }
    return pad;
}

#endif
