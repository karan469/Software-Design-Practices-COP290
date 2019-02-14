#include <iostream>
#include <algorithm>
#include "../functions.h"
#define Vector_Matrix_Float vector<vector<float>>
#define Vector_Tetris_Float vector<vector<vector<float>>>



// class poolingKernel{
// private:
// 	Vector_Matrix_Float poolings[6];
// 	void updatePoolings(int i, Vector_Matrix_Float v){
// 		poolings[i] = v;
// 	}
// 	Vector_Matrix_Float returnIthPooling(int i){
// 		return poolings[i];
// 	}
// };

// Vector_Tetris_Float updateSheetOfTetris(Vector_Tetris_Float v, int rows, int coloumns,int h, Vector_Matrix_Float v1){
// 	Vector_Tetris_Float vnew(v1.size(),vector<vector<float>(v1[0].size(),vector<float>(h,0.0)));
// 	for(int i=0;i<rows;i++){
// 		for(int j=0;j<coloumns;j++){
// 			v[i][j][h] = v1[i][j];
// 		}
// 	}
// 	return v;
// }

Vector_Matrix_Float giveOneSheet(Vector_Tetris_Float v, int rows, int coloumns, int h){
	Vector_Matrix_Float v1(rows,vector<float>(coloumns,0.0));
	for(int i=0;i<rows;i++){
		for (int j = 0; j < coloumns; j++)
		{
			v1[i][j] = v[i][j][h];
		}
	}
}

Vector_Tetris_Float Conv_1(Vector_Matrix_Float image){
	kernels k;
	int rows = image.size();
	int coloumns = image[0].size();
	Vector_Tetris_Float v(rows,vector<vector<float>>(coloumns,vector<float>(6,0.0)));
	for(int i=0;i<6;i++){
		for(int j=0;j<rows;j++){
			for(int k=0;k<coloumns;k++){
				v[j][k][i] = convolution_matrixmult_mkl(image,k.filters[i],"intelmkl")[j][k];
				//DO BIAS
			}
		}
	}
	return v;
}

Vector_Tetris_Float Pool_1(Vector_Tetris_Float image3d){
	// poolingKernel p;

	Vector_Tetris_Float v(12,vector<vector<float>>(12,vector<float>(20,0.0)));
	
	Vector_Matrix_Float updatedSheet(12,vector<float>(12,0.0));
	for(int as=0;as<20;as++){
		updatedSheet = Pooling(giveOneSheet(image3d,24,24,as),"max",2);
		//v = updateSheetOfTetris(image3d,rows,coloumns,as,updatedSheet);
		//For this height 'as' changing of the sheet
		for(int i=0;i<12;i++){
			for(int j=0;j<12;j++){
				v[i][j][as] = updatedSheet[i][j];
			}
		}
	}
	return v;
}

Vector_Tetris_Float Conv_2(Vector_Tetris_Float image3d, Vector_Tetris_Float filter){
	//image3d: 12 X 12 X 20
	//filter: 5 X 5 X 20
	Vector_Tetris_Float v(8,vector<vector<float>(8,vector<float>(50,0.0)));
	v = convolution3d(image3d,12,filter,5,20);//convolution3d() to be made
	//DO BIAS
	return v;
}

Vector_Tetris_Float Pool_2(Vector_Tetris_Float image3d){
	//image3d: 8 X 8 X 50
	Vector_Tetris_Float v(4,vector<vector<float>>(4,vector<float>(50,0.0)));

	Vector_Matrix_Float updatedSheet(4,vector<float>(4,0.0));
	for(int as=0;as<50;as++){
		updatedSheet = Pooling(giveOneSheet(image3d,8,8,as),"max",2);
		//v = updateSheetOfTetris(image3d,rows,coloumns,as,updatedSheet);
		//For this height 'as' changing of the sheet
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				v[i][j][as] = updatedSheet[i][j];
			}
		}
	}
	return v;
}

// Vector_Tetris_Float volumeConvolution(Vector_Tetris_Float image3d, int n1, Vector_Tetris_Float kernel, int n2){

// }

Vector_Tetris_Float FC_1(Vector_Tetris_Float image3d, vector<vector<vector<vector<float> > > > filter){
	Vector_Tetris_Float v(1,vector<vector<float>>(1,vector<float>(500,0.0)));
	Vector_Tetris_Float filterCube(4,vector<vector<float>>(4,vector<float>(50,0.0)));
	for(int i=0;i<500;i++){
		
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				for(int t=0;t<50;t++){
					filterCube[j][k][t] = filter[j][k][t][i];
				}
			}
		}
		v[0][0][i] = convolution3d(image3d, 4, filterCube, 4, 50);
		//DO BIAS
	}
	return v;
}

Vector_Matrix_Float FC_half(Vector_Tetris_Float outFromFC1){
	Vector_Matrix_Float inForFC2(1,vector<float>(500,0.0));
	for(int h=0;h<500;h++){
		inForFC2[0][h] = outFromFC1[0][0][h];
	}
	return inForFC2;
}

Vector_Matrix_Float FC_2(Vector_Matrix_Float inForFC2, Vector_Matrix_Float filters){
	//this gives 1 X 10
	Vector_Matrix_Float v(1,vector<float>(10,0.0));
	v = convolution_matrixmult_mkl(inForFC2, filters);
	//DO BIAS
	return v;
}

int main(int argc, char const *argv[])
{
	cout<<"Hello"<<endl;
	return 0;
}