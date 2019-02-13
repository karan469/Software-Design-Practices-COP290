#include <iostream>
#include <algorithm>
#include "functions.h"

#define Vector_Matrix_Float vector<vector<float>>
#define Vector_Tetris_Float vector<vector<vector<float>>>
#define Vector_Quadris_Float vector<vector<vector<vector<float>>>>

struct filterAndBias {
    Vector_Tetris_Float filter;
    Vector_Matrix_Float bias;
};
struct filterAndBias4d {
    Vector_Quadris_Float filter;
    Vector_Matrix_Float bias;
};



Vector_Matrix_Float giveOneSheet(Vector_Tetris_Float v, int rows, int coloumns, int h){
	Vector_Matrix_Float v1(rows,vector<float>(coloumns,0.0));
	for(int i=0;i<rows;i++){
		for (int j = 0; j < coloumns; j++)
		{
			v1[i][j] = v[h][i][j];
		}
	}
	return v1;
}

Vector_Tetris_Float Conv_1(Vector_Matrix_Float image){
	struct filterAndBias data;
	data = filterBias("conv1.txt",5,20,20);
	Vector_Tetris_Float v(20,vector<vector<float>>(24,vector<float>(24,0.0)));
	for(int i=0;i<20;i++){
		Vector_Matrix_Float tempmatrix = convolution_matrixmult_mkl(image,data.filter[i],"intelmkl");
		for(int j=0;j<24;j++){
			for(int k=0;k<24;k++){
				v[i][j][k] = tempmatrix[j][k] + data.bias[i][0];///no use of zero
			}
		}
	}
	return v;
}

Vector_Tetris_Float Pool_1(Vector_Tetris_Float image3d,int rows,int coloumns){
	// poolingKernel p;
	struct filterAndBias data;
	data = filterBias("conv2.txt",5,20,20);
	Vector_Tetris_Float v(20,vector<vector<float>>(12,vector<float>(12,0.0)));
	
	Vector_Matrix_Float updatedSheet(12,vector<float>(12,0.0));
	for(int as=0;as<20;as++){
		updatedSheet = Pooling(giveOneSheet(image3d,24,24,as),"max",2);
		//v = updateSheetOfTetris(image3d,rows,coloumns,as,updatedSheet);
		//For this height 'as' changing of the sheet
		for(int i=0;i<12;i++){
			for(int j=0;j<12;j++){
				v[as][i][j] = updatedSheet[i][j];
			}
		}
	}
	return v;
}

Vector_Tetris_Float convolution3dH(struct filterAndBias4d data,Vector_Tetris_Float image3d,int a,int b,int c,int d)
{

	Vector_Tetris_Float v(c,vector<vector<float>>(d,vector<float>(a,0.0)));
	for(int l = 0; l < a; l++)
	{
		for(int k = 0; k < b; k++)
		{
			Vector_Matrix_Float tempmatrix = convolution_matrixmult_mkl(image3d[k],data.filter[l][k],"intelmkl");
			for(int i = 0; i < c; i++)
			{	
				for(int j = 0; j < d; j++)
				{
					v[l][i][j] += tempmatrix[i][j];
				}
				
			}
			
		}
		
	}
	for(int l = 0; l < a; l++)
	{
		for(int i = 0; i < c; i++)
		{
			for(int j = 0; j < d; j++)
			{
				v[l][i][j] += data.bias[l][0];
			}
			
		}
		
	}
	return v;
}


Vector_Tetris_Float Conv_2(Vector_Tetris_Float image3d){
	//image3d: 12 X 12 X 20
	//filter: 5 X 5 X 20
	struct filterAndBias4d data;
	data = filterBias4d("conv2.txt",50,5,50,20);
	Vector_Tetris_Float v(8,vector<vector<float>>(8,vector<float>(50,0.0)));

	v = convolution3dH(data,image3d,50,20,8,8);

	
	return v;
}

Vector_Tetris_Float Pool_2(Vector_Tetris_Float image3d){
	//image3d: 8 X 8 X 50
	Vector_Tetris_Float v(50,vector<vector<float>>(4,vector<float>(4,0.0)));

	Vector_Matrix_Float updatedSheet(4,vector<float>(4,0.0));
	for(int as=0;as<50;as++){
		updatedSheet = Pooling(giveOneSheet(image3d,8,8,as),"max",2);
		//v = updateSheetOfTetris(image3d,rows,coloumns,as,updatedSheet);
		//For this height 'as' changing of the sheet
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				v[as][i][j] = updatedSheet[i][j];
			}
		}
	}
	return v;
}



Vector_Tetris_Float FC_1(Vector_Tetris_Float image3d){
	struct filterAndBias4d data;
	data = filterBias4d("fc1.txt",500,4,500,50);
	Vector_Tetris_Float v(500,vector<vector<float>>(1,vector<float>(1,0.0)));

	v = convolution3dH(data,image3d,500,50,1,1);
	return v;
}

Vector_Tetris_Float FC_2(Vector_Tetris_Float image3d){
	struct filterAndBias4d data;
	data = filterBias4d("fc2.txt",10,1,10,500);
	Vector_Tetris_Float v(500,vector<vector<float>>(1,vector<float>(1,0.0)));

	v = convolution3dH(data,image3d,100,500,1,1);
	return v;
}

int main(int argc, char const *argv[])
{
	cout<<"Hello"<<endl;
	return 0;
}
