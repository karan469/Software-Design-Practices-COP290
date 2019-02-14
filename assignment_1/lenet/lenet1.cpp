#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "../Pooling.h"
#include "../convolution_mkl.h"
#include "../sigmoid_softmax.h"
#include "../convolution.h"
#include "../printHead.h"
#include "../convolution_pthread.h"
#include "takeFilters.h"
#include "/home/karan/intel/compilers_and_libraries_2019.1.144/linux/mkl/include/mkl.h"

#define float_Vector vector<float>
#define Vector_Matrix_Float vector<vector<float>>
#define Vector_Tetris_Float vector<vector<vector<float>>>
#define Vector_Quadris_Float vector<vector<vector<vector<float>>>>
using namespace std;

// struct filterAndBias {
//     Vector_Tetris_Float filter;
//     Vector_Matrix_Float bias;
// };
// struct filterAndBias4d {
//     Vector_Quadris_Float filter;
//     Vector_Matrix_Float bias;
// };

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
		Vector_Matrix_Float tempmatrix = convolution_matrixmult_mkl(data.filter[i],image,"intelmkl");
		for(int j=0;j<24;j++){
			for(int k=0;k<24;k++){
				v[i][j][k] = tempmatrix[j][k] + data.bias[i][0];///no use of zero
			}
		}
	}

	return v;
}

Vector_Tetris_Float Pool_1(Vector_Tetris_Float image3d){
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

Vector_Matrix_Float addMatrices(Vector_Matrix_Float v1, Vector_Matrix_Float v2){
	//jus adding cell by cell
	//assuming dimensions same
	
	int rows = v1.size();
	int coloumns = v1[0].size();
	Vector_Matrix_Float v(rows, vector<float>(coloumns, 0.0));
	for(int i=0;i<rows;i++){
		for(int j=0;j<coloumns;j++){
			v[i][j] = v1[i][j] + v2[i][j];
		}
	}
	return v;
}

// Vector_Tetris_Float convoltion3dd(struct filterAndBias4d data, Vector_Tetris_Floatimage3d)

// Vector_Tetris_Float convolution3dH(struct filterAndBias4d data,Vector_Tetris_Float image3d,int a,int b,int c,int d)
// {
// 	//a: output channel depth
// 	//b: input channel depth
// 	//c, d: output sheet dimension
// 	Vector_Tetris_Float v(c,vector<vector<float>>(d,vector<float>(a,0.0)));
// 	for(int l = 0; l < a; l++)
// 	{
// 		for(int k = 0; k < b; k++)
// 		{
// 			Vector_Matrix_Float tempmatrix = convolution_matrixmult_mkl(data.filter[l][k],image3d[k],"intelmkl");
// 			for(int i = 0; i < c; i++)
// 			{	
// 				for(int j = 0; j < d; j++)
// 				{
// 					v[l][i][j] += tempmatrix[i][j];
// 				}	
// 			}
// 		}
// 	}
// 	for(int l = 0; l < a; l++)
// 	{
// 		for(int i = 0; i < c; i++)
// 		{
// 			for(int j = 0; j < d; j++)
// 			{
// 				v[l][i][j] += data.bias[l][0];
// 			}	
// 		}
// 	}
// 	return v;
// }

Vector_Tetris_Float Conv_2(Vector_Tetris_Float image3d){
	//image3d: 12 X 12 X 20
	//filter: 5 X 5 X 20
	
	struct filterAndBias4d data;
	data = filterBias4d("conv2.txt",50,5,50,20);
	Vector_Tetris_Float v(50,vector<vector<float>>(8,vector<float>(8,0.0)));

	
	//5*5*20*50 | 12*12*20

	// v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][0], image3d[0], "intelmkl"));
	// print(v[0]);
	
	//Karan, doing his convo3d
	for(int i=0;i<50;i++){
		//for(int j=0;j<20;j++){
			//v[i] = addMatrices(v[i], convolution_matrixmult_pthread(data.filter[i][j], image3d[j])) ;
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][0], image3d[0], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][1], image3d[1], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][2], image3d[2], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][3], image3d[3], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][4], image3d[4], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][5], image3d[5], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][6], image3d[6], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][7], image3d[7], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][8], image3d[8], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][9], image3d[9], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][10], image3d[10], "intelmkl"));

			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][11], image3d[11], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][12], image3d[12], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][13], image3d[13], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][14], image3d[14], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][15], image3d[15], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][16], image3d[16], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][17], image3d[17], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][18], image3d[18], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][19], image3d[19], "intelmkl"));
		//}
	}
	//Added BIAS//
	for(int q=0;q<50;q++){
		for(int a=0;a<8;a++){
			for(int b=0;b<8;b++){
				v[q][a][b] += data.bias[q][0];
			}
		}
	}
	// v = convolution3dH(data,image3d,50,20,8,8);
	
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
	//image3d: 4*4*50
	struct filterAndBias4d data;
	data = filterBias4d("fc1.txt",500,4,500,50);
	Vector_Tetris_Float v(500,vector<vector<float>>(1,vector<float>(1,0.0)));


	//3D CONVOLUTION//
	//print(data.filter[1][10]);
	for(int i=0;i<500;i++){
		//cout<<"asdasd"<<endl;
		//for(int j=0;j<20;j++){
			//v[i] = addMatrices(v[i], convolution_matrixmult_pthread(data.filter[i][j], image3d[j])) ;
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][0], image3d[0], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][1], image3d[1], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][2], image3d[2], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][3], image3d[3], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][4], image3d[4], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][5], image3d[5], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][6], image3d[6], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][7], image3d[7], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][8], image3d[8], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][9], image3d[9], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][10], image3d[10], "intelmkl"));

			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][11], image3d[11], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][12], image3d[12], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][13], image3d[13], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][14], image3d[14], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][15], image3d[15], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][16], image3d[16], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][17], image3d[17], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][18], image3d[18], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][19], image3d[19], "intelmkl"));

			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][20], image3d[20], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][21], image3d[21], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][22], image3d[22], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][23], image3d[23], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][24], image3d[24], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][25], image3d[25], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][26], image3d[26], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][27], image3d[27], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][28], image3d[28], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][29], image3d[29], "intelmkl"));

			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][30], image3d[30], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][31], image3d[31], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][32], image3d[32], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][33], image3d[33], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][34], image3d[34], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][35], image3d[35], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][36], image3d[36], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][37], image3d[37], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][38], image3d[38], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][39], image3d[39], "intelmkl"));

			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][40], image3d[40], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][41], image3d[41], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][42], image3d[42], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][43], image3d[43], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][44], image3d[44], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][45], image3d[45], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][46], image3d[46], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][47], image3d[47], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][48], image3d[48], "intelmkl"));
			v[i] = addMatrices (v[i],convolution_matrixmult_mkl(data.filter[0][49], image3d[49], "intelmkl"));
		//}
	}
	//Added Biasing//
	for(int q=0;q<500;q++){
		for(int a=0;a<1;a++){
			for(int b=0;b<1;b++){
				v[q][a][b] += data.bias[q][0];
			}
		}
	}
	// v = convolution3dH(data,image3d,500,50,1,1);
	return v;
}

Vector_Tetris_Float FC_2(Vector_Tetris_Float image3d){
	//v: 1*1*10
	//image3d: 1*1*500
	struct filterAndBias4d data;
	data = filterBias4d("fc2.txt",10,1,10,500);
	Vector_Tetris_Float v(10,vector<vector<float>>(1,vector<float>(1,0.0)));

	// 3D CONVOLUTION
	Vector_Matrix_Float filterSheet;
	for(int i=0;i<10;i++){
		for(int j=0;j<500;j++){
			filterSheet = data.filter[i][j];
			filterSheet = convolution_matrixmult_mkl(filterSheet,image3d[j],"intelmkl");
			//v[i] = addMatrices(v[i], convolution_matrixmult_mkl(data.filter[i][j], image3d[j],"intelmkl")) ;
			v[i] = addMatrices(v[i],filterSheet);
		}
	}
	//Added BIAS
	for(int q=0;q<10;q++){ //10 bias values
		for(int a=0;a<1;a++){
			for(int b=0;b<1;b++){
				v[q][a][b] += data.bias[q][0];
			}
		} 
	}

	// v = convolution3dH(data,image3d,100,500,1,1);
	return v;
}

vector<float> FC_Final(Vector_Tetris_Float image3d){
	//change 1*1*500 to 1*500 but in reversed form so , its actually 500*1
	//Vector_Matrix_Float v(10,vector<float>(1,0.0));
	vector<float> v(10,0.0);
	for(int i=0;i<10;i++){
		v[i] = image3d[i][0][0];
	}
	return v;
}



Vector_Matrix_Float imageFromText(string filename){
	fstream infile;
	infile.open(filename);
	if(!infile.is_open()){
		cout<<"File of this name doesn't exist"<<endl;
	}
	float p;
	string line = "";
	Vector_Matrix_Float vi(28,vector<float>(28,0.0));
	for(int f=0;f<28;f++){
		for(int g=0;g<28;g++){
			getline(infile,line);
			if(line!=""){
				stringstream num(line);
				num >> p;
				vi[f][g] = (float)(p);//Image Normalized here <-- Check how is it actual normalization
			}
		}
	}
	return vi;
}

vector<float> mainController(string filename){
	Vector_Matrix_Float image(28,vector<float>(28,0.0));
	image = imageFromText(filename);
	return (FC_Final(FC_2(FC_1(Pool_2(Conv_2(Pool_1(Conv_1(image))))))));
}

int main()
{
	//print(Conv_1(imageFromText("1_new.txt"))[0]); //testing result from Conv_1

	//print(imageFromText("1_new.txt"));//image matrix from txt
	print(mainController("2_new.txt"));//final output
	cout<<endl;
	
	return 0;
}
