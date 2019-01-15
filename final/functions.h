#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <fstream>
#include <sstream>
#define Vector_Matrix vector<vector<int>>

#define Vector_Matrix_Float vector<vector<float>>
#define float_Vector vector<float>
using namespace std;
void print_vector_matrix_float(Vector_Matrix_Float v);
void print_float_vector(float_Vector v);
float makeRelu(float a);
float makeTanh(float a);
Vector_Matrix_Float reluMatrix(Vector_Matrix_Float v);
Vector_Matrix_Float tanhMatrix(Vector_Matrix_Float v);
Vector_Matrix_Float randomVectorMatrixGenerator(int m, int n);

void print_sum(float_Vector v);
float_Vector sigmoid(float_Vector a);
float_Vector softmax(float_Vector a);

void print_vector_matrix(Vector_Matrix v);
int sub_convo(Vector_Matrix v1, Vector_Matrix v2);
Vector_Matrix convolution_matrixmult(Vector_Matrix v1, Vector_Matrix v2);
Vector_Matrix convolution(Vector_Matrix v1, Vector_Matrix v2);
Vector_Matrix convolution_pad(Vector_Matrix v2, int padding);

Vector_Matrix Pooling(Vector_Matrix v1, string pool,int stride);





