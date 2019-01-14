#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <fstream>
#include <sstream>
#include "convolution.h"
#include "sigmoid_softmax.h"
#include "Pooling.h"
#include "relu_tanh.h"
#include "printHead.h"
using namespace std;
#define Vector_Matrix vector<vector<int>>
#define Vector_Matrix_Float vector<vector<float>>


Vector_Matrix conv_in_matrix(char const *argv[],int n,int m){ // argv[m] contains matrix.txt // argv[n] contains now of rows
    stringstream convert1(argv[n]);
    int size;
    if (!(convert1 >> size)) // do the conversion
        size = 0; // if conversion fails, set myint to a default value
    
    // main matrix v2
    ifstream infile(argv[m]);
    string line ="";
    Vector_Matrix v2(size, vector<int>(size,0));
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
        {
            getline(infile, line);
            if(line != "")
            {
                stringstream num(line);
                num >> n;
                v2[j][i] = n;
            }
        }    
    }
    return v2;
}









Vector_Matrix_Float conv_in_matrix_float(char const *argv[],int n,int m){ // argv[m] contains matrix.txt // argv[n] contains now of rows
    stringstream convert1(argv[n]);
    int size;
    if (!(convert1 >> size)) // do the conversion
        size = 0; // if conversion fails, set myint to a default value
    
    // main matrix v2
    ifstream infile(argv[m]);
    string line ="";
    Vector_Matrix_Float v2(size, vector<float>(size,0.0));
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
        {
            getline(infile, line);
            if(line != "")
            {
                stringstream num(line);
                num >> n;
                v2[j][i] = (float)n;
            }
        }    
    }
    return v2;
}









int checker(char const *argv[], string forwhat)
{
    int n;
    if(forwhat == "convolution")
    {
        if(sscanf(argv[3],"%d",&n) && sscanf(argv[5],"%d",&n) && argv[6]==NULL);
        else 
        {
            cout<< "Wrong Syntax" << endl;
            cout<< "Expected - ";
            cout<< argv[1] << " [matrix1.txt] [matrix1_size] [matrix2.txt] [matrix1_size]" << endl;
            return 0;
        }
    }
    else if(forwhat == "pooling")
    {
        if(sscanf(argv[4],"%d",&n) && sscanf(argv[5],"%d",&n) && argv[6]==NULL);
        else
        {
            cout<< "Wrong Syntax" << endl;
            cout<< "Expected - ";
            cout<< argv[1] << " [type] [matrix1.txt] [matrix1_size] [stride]" << endl;
            return 0;
        }
    }
    else if(forwhat == "softmax")
    {
        if(sscanf(argv[3],"%d",&n) && argv[4]==NULL);
        else
        {
            cout<< "Wrong Syntax" << endl;
            cout<< "Expected - ";
            cout<< argv[1] << " [matrix1.txt] [matrix1_size] [stride]" << endl;
            return 0;
        }
    }
    else if(forwhat == "sigmoid")
    {
        //cout<<sscanf(argv[3],"%d",&n);
        if(sscanf(argv[3],"%d",&n) && argv[4]==NULL);
        else
        {
            cout<< "Wrong Syntax" << endl;
            cout<< "Expected - ";
            cout<< argv[1] << " [matrix1.txt] [matrix1_size] [stride]" << endl;
            return 0;
        }
    } else if(forwhat=="tanh_activation"){
        if(sscanf(argv[3],"%d",&n) && argv[4]==NULL);
        else
        {
            cout<<"Wrong Syntax"<<endl;
            cout<<"Expected - ";
            cout<<argv[1]<<" [matrix1.txt] [matrix1_size]"<<endl;
            return 0;
        }
    }//./main.out relu_activation matrix1.txt matrix_numrows 
    else if(forwhat=="relu_activation"){
        if(sscanf(argv[3],"%d",&n) && argv[4]==NULL);
        else
        {
            cout<<"Wrong Syntax"<<endl;
            cout<<"Expected - ";
            cout<<argv[1]<<" [matrix1.txt] [matrix1_size]"<<endl;
            return 0;
        }
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    int lulu = 0;
    string check ="";
    if(argv[1]){
        stringstream strtake(argv[1]);
        strtake >> check;
    } else {
        lulu++;
    }   
    
    
    //this is of the form
    // ./main.out convolution_withpadding_matrixmult matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
    if(check == "convolution_withpadding_matrixmult"){
        //Read the file
        if(!checker(argv,"convolution"))
        {
            return 0;
        }

        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,3,2);

        
        Vector_Matrix v1;
        v1 = conv_in_matrix(argv,5,4);
        int size2 = v1[0].size();
        int padding = (size2-1)/2;
        v2 = convolution_pad(v2,padding);
        print(convolution_matrixmult(v1,v2));
    }
    else if(check == "convolution_withoutpadding_matrixmult"){
        //Read the file
        if(!checker(argv,"convolution"))
        {
            return 0;
        }
        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,3,2);

        
        Vector_Matrix v1;
        v1 = conv_in_matrix(argv,5,4);
        int size2 = v1[0].size();
        int padding = (size2-1)/2;//optimal but not used now
        // v2 = convolution_pad(v2,padsize);
        print(convolution_matrixmult(v1,v2));

    }
    // ./main.out convolution_withpadding padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
    else if(check == "convolution_withpadding"){
        //Read the file
        if(!checker(argv,"convolution"))
        {
            return 0;
        }
        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,3,2);
        Vector_Matrix v1 = conv_in_matrix(argv,5,4);
        print(convolution((conv_in_matrix(argv,5,4)),(convolution_pad(v2,(((v1[0].size())-1)/2)))));
    }
    else if(check == "convolution_withoutpadding"){
        //Read the file
        if(!checker(argv,"convolution"))
        {
            return 0;
        }
        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,3,2);

        
        Vector_Matrix v1;
        v1 = conv_in_matrix(argv,5,4);
        int size2 = v1[0].size();
        int padding = (size2-1)/2;//optimal but not used now
        // v2 = convolution_pad(v2,padsize);
        print(convolution(v1,v2));

    }
    //// ./main.out pooling max matrix1.txt matrix1_numrows fil_size
    //// ./main.out pooling avg matrix1.txt matrix1_numrows fil_size
    else if(check == "pooling"){
        if(!checker(argv,"pooling"))
        {
            return 0;
        }
        string pool = "";
        stringstream convert(argv[2]);
        convert >> pool;
        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,4,3);
        int fil_size = 0;
        stringstream convert2(argv[5]);
        convert2 >> fil_size;
        print(Pooling(v2,pool,fil_size));
        
    } //./main.out relu_activation matrix1.txt matrix_numrows
    else if(check=="relu_activation"){
        if(!checker(argv, "relu_activation")){
            return 0;
        }
        //DO OPS HERE!!!
        Vector_Matrix_Float v;
        v = conv_in_matrix_float(argv,3,2);
        print(reluMatrix(v));
    } //./main.out tanh_activation matrix1.txt matrix_numrows 
    else if(check=="tanh_activation"){
        if(!checker(argv, "tanh_activation")){
            return 0;
        }
        //DO OPS HERE !!
        Vector_Matrix_Float v;
        v = conv_in_matrix_float(argv,3,2);
        print(tanhMatrix(v));
        
    }
    // ./main.out softmax matrix1.txt matrix1_numrows
    else if(check == "softmax"){
        if(!checker(argv,"softmax"))
        {
            return 0;
        }
        stringstream convert1(argv[3]);
        int size;
        if (!(convert1 >> size)) // do the conversion
            size = 0; // if conversion fails, set myint to a default value
        
        // main matrix v2
        ifstream infile(argv[2]);
        string line ="";
        int n = 0;
        vector<float> v2(size, 0.0);
        
        for(int i = 0; i < size; i++){
            getline(infile, line);
            if(line != "")
            {
                stringstream num(line);
                num >> n;
                v2[i] = n;
            }
            
        } 
        print(softmax(v2));
    }
    // ./main.out sigmoid matrix1.txt matrix1_numrows
    else if(check == "sigmoid"){
        if(!checker(argv,"sigmoid"))
        {
            return 0;
        }
        stringstream convert1(argv[3]);
        int size;
        if (!(convert1 >> size)) // do the conversion
            size = 0; // if conversion fails, set myint to a default value
        
        // main matrix v2
        ifstream infile(argv[2]);
        string line ="";
        int n = 0;
        vector<float> v2(size, 0.0);
        
        for(int i = 0; i < size; i++){
            getline(infile, line);
            if(line != "")
            {
                stringstream num(line);
                num >> n;
                v2[i] = n;
            }
            
        } 
        print(sigmoid(v2));
    }
    else{
        cout << "None of the above functions written:" << endl;
        cout << "'convolution_withpadding_matrixmult'" << endl;
        cout << "'convolution_withoutpadding_matrixmult'" << endl;
        cout << "'pooling'" << endl;
        cout << "'sigmoid'" << endl;
        cout << "'softmax'" << endl;
    }
    return 0;
}

// ./main.out convolution_withpadding_matrixmult matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
//  argv[0]   argv[1]                            argv[2]     argv[3]         argv[4]     argv[5]
