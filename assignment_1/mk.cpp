#include <iostream>
#include <vector>
#include "/home/karan/intel/compilers_and_libraries_2019.1.144/linux/mkl/include/mkl.h"
// #include <stdlib>
#define min(x,y) ((x>y) ? y : x)
using namespace std;
#define Vector_Matrix_Float vector<vector<float>>
#define MAX_IMAGE_SIZE 100000

Vector_Matrix_Float linearToVectorMatrix(double a[MAX_IMAGE_SIZE], int m, int n)
{
	Vector_Matrix_Float v(m,vector<float>(n,0.0));
	
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			v[i][j] = a[i+j];
		}
	}
	
	return v;
}

void print(Vector_Matrix_Float v){
    cout<<"Printing vector: "<<endl;
    for(int i=0;i<v.size();i++){
      for(int j=0;j<v[0].size();j++){
          cout<<v[i][j]<<" ";
          
      }
      cout<<endl;
  }
}

int main(){
	//int ar[10][20];
	double *A,*B,*C;
	int m,n,k,i,j;
	double alpha, beta;
	m=4, k=4,n=1;
	alpha = 1.0;
	beta = 0.0;

	A = (double *)mkl_malloc( m*k*sizeof( double ), 8 );
	B = (double *)mkl_malloc( k*n*sizeof( double ), 8 );
	C = (double *)mkl_malloc( m*n*sizeof( double ), 8 );
	if(A ==NULL || B==NULL || C==NULL) {
		cout<<"Cannot allocate memory for matrices. Aborting... \n\n";
		mkl_free(A);
		mkl_free(B);
		mkl_free(B);
		return 1;
	}
	cout<<"Initializing matrix data \n\n";
	for(i=0;i<(m*k);i++){
		// for(int p=0;p<k;p++){
		// 	A[i][p] = (double)(i+p+1);
		// }
		//cout<<A[2];
		*(A + i) = (double)(i+1);
		//cout<<A[i]<<"***"<<endl;
	}
	
	// for(i=0;i<(k*n);i++){
	// 	B[i] = (double)(-i-1);
	// 	//cout<<B[i]<<"*******";
	// }
	B[0] = 1.0;
	B[1] = 2.0;
	B[2] = -2.0;
	B[3] = 1.0;
	for(i=0;i<(m*n);i++){
		C[i] = 0.0;
		//cout<<C[i]<<"------------"<<endl;
	}
	cout<<"Done..";
	cout<<"Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface\n\n";
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,m,n,k,alpha,A,k,B,n,beta,C,n);
	cout<<"Computation completed.\n\n";

	// online se utara
	// for (i=0; i<min(m,6); i++) {
	// 	for (j=0; j<min(n,6); j++) { //changes min(k,6) to min(n,6)
	// 		cout<<C[j+i*k]<<"*";
	// 	}
	// 	cout<<"\n";
	// }
	
	//Khud socha but bekaar socha
	// for(int p=0;p<(m*n);p++){
	// 	cout<<C[p];
	// }
	
	print(linearToVectorMatrix(C,m,n));

	cout<<"\nDeallocating memory \n\n";
	mkl_free(A);
	mkl_free(B);
	mkl_free(C);
	return 0;

}
