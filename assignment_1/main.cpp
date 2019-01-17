#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <fstream>
#include <sstream>
#include "functions.h"
// #include "sigmoid_softmax.h"
// #include "Pooling.h"
// #include "relu_tanh.h"
// #include "printHead.h"
using namespace std;
#define Vector_Matrix vector<vector<int>>
#define Vector_Matrix_Float vector<vector<float>>

// flfk
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
    cout << size << endl;
    // main matrix v2
    fstream infile;
        infile.open(argv[m]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
        }
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
        if(argv[3]!=NULL && sscanf(argv[3],"%d",&n) && argv[5]!=NULL && sscanf(argv[5],"%d",&n) && argv[6]==NULL);
        else 
        {
            cout<< "Wrong Syntax" << endl;
            cout<< "Expected - ";
            cout<< argv[1] << " [matrix1.txt] [matrix1_size] [matrix2.txt] [matrix1_size]" << endl;
            return 0;
        }

        fstream infile;
        infile.open(argv[2]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }
        infile.close();
        fstream infile1;
        infile1.open(argv[4]);
        if(!infile1.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }
        infile1.close();

    }
    else if(forwhat == "pooling")
    {
        if(argv[4]!=NULL && sscanf(argv[4],"%d",&n) && argv[5]!=NULL  && sscanf(argv[5],"%d",&n) && argv[6]==NULL);
        else
        {
            cout<< "Wrong Syntax" << endl;
            cout<< "Expected - ";
            cout<< argv[1] << " [type] [matrix1.txt] [matrix1_size] [stride]" << endl;
            return 0;
        }
        fstream infile;
        infile.open(argv[3]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }
        infile.close();
    }
    else if(forwhat == "softmax")
    {
        if(argv[3]!=NULL && sscanf(argv[3],"%d",&n) && argv[4]==NULL);
        else
        {
            cout<< "Wrong Syntax" << endl;
            cout<< "Expected - ";
            cout<< argv[1] << " [matrix1.txt] [matrix1_size] [stride]" << endl;
            return 0;
        }

        fstream infile;
        infile.open(argv[2]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }

        infile.close();
    }
    else if(forwhat == "sigmoid")
    {
        //cout<<sscanf(argv[3],"%d",&n);
        if(argv[3]!=NULL && sscanf(argv[3],"%d",&n) && argv[4]==NULL);
        else
        {
            cout<< "Wrong Syntax" << endl;
            cout<< "Expected - ";
            cout<< argv[1] << " [matrix1.txt] [matrix1_size] [stride]" << endl;
            return 0;
        }
        fstream infile;
        infile.open(argv[2]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }

        infile.close();
    } else if(forwhat=="tanh_activation"){
        
        if(argv[3]!=NULL && sscanf(argv[3],"%d",&n) && argv[4]==NULL);
        else
        {
            cout<<"Wrong Syntax"<<endl;
            cout<<"Expected - ";
            cout<<argv[1]<<" [matrix1.txt] [matrix1_size]"<<endl;
            return 0;
        }
         fstream infile;
        infile.open(argv[2]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }

        infile.close();
    }//./main.out relu_activation matrix1.txt matrix_numrows 
    else if(forwhat=="relu_activation"){
         
        if(argv[3]!=NULL && sscanf(argv[3],"%d",&n) && argv[4]==NULL);
        else
        {
            cout<<"Wrong Syntax"<<endl;
            cout<<"Expected - ";
            cout<<argv[1]<<" [matrix1.txt] [matrix1_size]"<<endl;
            return 0;
        }
        fstream infile;
        infile.open(argv[2]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }
        infile.close();
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
        stringstream convert5(argv[3]);
        int check1;
        convert5 >> check1;
        stringstream convert6(argv[5]);
        int check2;
        convert6 >> check2;
        if(check1 < 0 || check2 < 0)
        {
            cout << "negative numbers are not permitted; these are against mathematics" << endl;
            return 0;
        }
        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,3,2);

        
        Vector_Matrix v1;
        v1 = conv_in_matrix(argv,5,4);
        int size2 = v1[0].size();
        int padding = (size2-1)/2;
        v2 = convolution_pad(v2,padding);
        print_vector_matrix(convolution_matrixmult(v1,v2));
    }
    else if(check == "convolution_withoutpadding_matrixmult"){
        //Read the file
        if(!checker(argv,"convolution"))
        {
            return 0;
        }
        stringstream convert5(argv[3]);
        int check1;
        convert5 >> check1;
        stringstream convert6(argv[5]);
        int check2;
        convert6 >> check2;
        if(check1 < 0 || check2 < 0)
        {
            cout << "Cannot be nagetive." << endl;
            return 0;
        }
        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,3,2);

        
        Vector_Matrix v1;
        v1 = conv_in_matrix(argv,5,4);
        int size2 = v1[0].size();
        int padding = (size2-1)/2;//optimal but not used now
        // v2 = convolution_pad(v2,padsize);
        print_vector_matrix(convolution_matrixmult(v1,v2));

    }
    // ./main.out convolution_withpadding padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
    else if(check == "convolution_withpadding"){
        //Read the file
        if(!checker(argv,"convolution"))
        {
            return 0;
        }
        stringstream convert5(argv[3]);
        int check1;
        convert5 >> check1;
        stringstream convert6(argv[5]);
        int check2;
        convert6 >> check2;
        if(check1 < 0 || check2 < 0)
        {
            cout << "Cannot be nagetive." << endl;
            return 0;
        }
        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,3,2);
        Vector_Matrix v1 = conv_in_matrix(argv,5,4);
        print_vector_matrix(convolution((conv_in_matrix(argv,5,4)),(convolution_pad(v2,(((v1[0].size())-1)/2)))));
    }
    else if(check == "convolution_withoutpadding"){
        //Read the file
        if(!checker(argv,"convolution"))
        {
            return 0;
        }
        stringstream convert5(argv[3]);
        int check1;
        convert5 >> check1;
        stringstream convert6(argv[5]);
        int check2;
        convert6 >> check2;
        if(check1 < 0 || check2 < 0)
        {
            cout << "Cannot be nagetive." << endl;
            return 0;
        }
        Vector_Matrix v2;
        v2 = conv_in_matrix(argv,3,2);

        
        Vector_Matrix v1;
        v1 = conv_in_matrix(argv,5,4);
        int size2 = v1[0].size();
        int padding = (size2-1)/2;//optimal but not used now
        // v2 = convolution_pad(v2,padsize);
        print_vector_matrix(convolution(v1,v2));

    }
    //// ./main.out pooling max matrix1.txt matrix1_numrows fil_size
    //// ./main.out pooling avg matrix1.txt matrix1_numrows fil_size
    else if(check == "pooling"){
        if(!checker(argv,"pooling"))
        {
            return 0;
        }
        stringstream convert5(argv[4]);
        int check1;
        convert5 >> check1;
        stringstream convert6(argv[5]);
        int check2;
        convert6 >> check2;
        if(check1 < 0 || check2 < 0)
        {
            cout << "Cannot be nagetive." << endl;
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
        print_vector_matrix(Pooling(v2,pool,fil_size));
        
    } //./main.out relu_activation matrix1.txt matrix_numrows
    else if(check=="relu_activation"){
        if(!checker(argv, "relu_activation")){
            return 0;
        }
        stringstream convert5(argv[3]);
        int check1;
        convert5 >> check1;
        if(check1 < 0)
        {
            cout << "Cannot be nagetive." << endl;
            return 0;
        }
        //DO OPS HERE!!!
        Vector_Matrix_Float v;
        v = conv_in_matrix_float(argv,3,2);
        print_vector_matrix_float(reluMatrix(v));
    } //./main.out tanh_activation matrix1.txt matrix_numrows 
    else if(check=="tanh_activation"){
        if(!checker(argv, "tanh_activation")){
            return 0;
        }
        stringstream convert5(argv[3]);
        int check1;
        convert5 >> check1;
        if(check1 < 0)
        {
            cout << "Cannot be nagetive." << endl;
            return 0;
        }
        //DO OPS HERE !!
        Vector_Matrix_Float v;
        v = conv_in_matrix_float(argv,3,2);
        print_vector_matrix_float(tanhMatrix(v));
        
    }
    // ./main.out softmax matrix1.txt matrix1_numrows
    else if(check == "softmax"){
        if(!checker(argv,"softmax"))
        {
            return 0;
        }
        stringstream convert5(argv[3]);
        int check1;
        convert5 >> check1;
        if(check1 < 0)
        {
            cout << "Cannot be nagetive." << endl;
            return 0;
        }
        stringstream convert1(argv[3]);
        int size;
        if (!(convert1 >> size)) // do the conversion
            size = 0; // if conversion fails, set myint to a default value
        
        // main matrix v2
        fstream infile;
        infile.open(argv[2]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }
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
        print_float_vector(softmax(v2));
    }
    // ./main.out sigmoid matrix1.txt matrix1_numrows
    else if(check == "sigmoid"){
        if(!checker(argv,"sigmoid"))
        {
            return 0;
        }
        stringstream convert5(argv[3]);
        int check1;
        convert5 >> check1;
        if(check1 < 0)
        {
            cout << "Cannot be nagetive." << endl;
            return 0;
        }
        stringstream convert1(argv[3]);
        int size;
        if (!(convert1 >> size)) // do the conversion
            size = 0; // if conversion fails, set myint to a default value
        
        // main matrix v2
        
        fstream infile;
        infile.open(argv[2]);
        if(!infile.is_open()){
            cout << "File given is not correct"<<endl;
            return 0;
        }
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
        print_float_vector(sigmoid(v2));
    }
    else{
        cout << "None of the above functions written:" << endl;
        cout << "'convolution_withpadding_matrixmult'" << endl;
        cout << "'convolution_withoutpadding_matrixmult'" << endl;
        cout << "'pooling'" << endl;
        cout << "'sigmoid'" << endl;
        cout << "'softmax'" << endl;
        cout << "'tanh_activation'" << endl;
        cout << "'relu_activation'" << endl;
    }
    return 0;
}

// ./main.out convolution_withpadding_matrixmult matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows
//  argv[0]   argv[1]                            argv[2]     argv[3]         argv[4]     argv[5]
