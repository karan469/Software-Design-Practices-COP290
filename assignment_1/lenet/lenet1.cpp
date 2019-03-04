#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "../imgProcess/Pooling.h"
#include "../imgProcess/convolution_mkl.h"
#include "../imgProcess/sigmoid_softmax.h"
#include "../imgProcess/convolution.h"
#include "../imgProcess/printHead.h"
#include "../imgProcess/relu_tanh.h"
#include "takeFilters.h"
#include "/home/karan/intel/compilers_and_libraries_2019.1.144/linux/mkl/include/mkl.h"

#define float_Vector vector<float>
#define Vector_Matrix_Float vector<vector<float>>
#define Vector_Tetris_Float vector<vector<vector<float>>>
#define Vector_Quadris_Float vector<vector<vector<vector<float>>>>
using namespace std;

Vector_Matrix_Float giveOneSheet(Vector_Tetris_Float v, int rows, int coloumns, int h){
	Vector_Matrix_Float v1(rows,vector<float>(coloumns,0.0));
	for(int i=0;i<rows;i++){
		for (int j = 0; j < coloumns; j++)
		{
			v1[i][j] = v[h][i][j];
		}
	}
	return v[h];
}

Vector_Matrix_Float rotateF(Vector_Matrix_Float filter){
	Vector_Matrix_Float v(filter.size(),vector<float>(filter[0].size(),0.0));
	for(int i=0;i<filter.size();i++){
		for(int j=0;j<filter.size();j++){
			v[(filter.size()-j-1)][(filter.size()-i-1)] = filter[i][j];
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
				vi[f][g] = 1-(float)(p/255);//Image Normalized here <-- Check how is it actual normalization
			}
		}
	}
	return vi;
}

Vector_Tetris_Float Conv_1(Vector_Matrix_Float image){
	struct filterAndBias data;
	data = filterBias("conv1.txt",5,20,20);
	Vector_Tetris_Float v(20,vector<vector<float>>(24,vector<float>(24,0.0)));

	for(int i=0;i<20;i++){
		v[i] = convolution_matrixmult_mkl(rotateF(data.filter[i]), image, "intelmkl");
	}
	for(int q=0;q<20;q++){
		for(int a=0;a<24;a++){
			for(int b=0;b<24;b++){
				v[q][a][b] += data.bias[q][0];
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
		updatedSheet = Pooling(image3d[as],"max",2);
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

// Second version of Pool_1 much cleaner but not using now coz its incomplete, bitch
// Vector_Tetris_Float Pool_1_1(Vector_Tetris_Float image3d){
// 	struct filterAndBias data;
// 	data = filterBias("conv2.txt",5,20,20);
// 	Vector_Tetris_Float v(20,vector<vector<float>>(12,vector<float>(12,0.0)));
// 	for(int i=0;i<20;i++){
// 		v[i] = Pooling(image3d[i],"max",2);
// 	}
// 	return v;
// }

// This funciton reminds me of ocaml, sounds good but is shit :/
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

	//God, doing his convo3d
	for(int i=0;i<50;i++){
		//for(int j=0;j<20;j++){
			//v[i] = addMatrices(v[i], convolution_matrixmult_pthread(data.filter[i][j], image3d[j])) ;
			for(int j = 0; j < 20; j++)
			{
				v[i] = addMatrices (v[i],convolution_matrixmult_mkl(rotateF(data.filter[i][j]), image3d[j], "intelmkl"));
			}
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
		updatedSheet = Pooling(image3d[as],"max",2);
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
	Vector_Tetris_Float v(500,vector<vector<float>>(1,vector<float>(1,0.0f)));

	//3D CONVOLUTION//
	//print(data.filter[1][10]);
	for(int i=0;i<500;i++){
		//cout<<"asdasd"<<endl;
		//for(int j=0;j<20;j++){
			//v[i] = addMatrices(v[i], convolution_matrixmult_pthread(data.filter[i][j], image3d[j])) ;
			for(int j = 0; j < 50; j++)
			{
				v[i] = addMatrices (v[i],convolution_matrixmult_mkl(rotateF(data.filter[i][j]), image3d[j], "intelmkl"));
			}
			

	}
	//Added Biasing//
	for(int q=0;q<500;q++){
		for(int a=0;a<1;a++){
			for(int b=0;b<1;b++){
				v[q][a][b] += data.bias[q][0];
			}
		}
	}
	for(int q=0;q<500;q++){
		for(int a=0;a<1;a++){
			for(int b=0;b<1;b++){
				v[q][a][b] = makeRelu(v[q][a][b]);
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
			filterSheet = convolution_matrixmult_mkl(rotateF(filterSheet),image3d[j],"intelmkl");
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
	vector<float> v(image3d.size(),0.0);
	for(int i=0;i<image3d.size();i++){
		v[i] = image3d[i][0][0];
	}
	return v;
}



vector<float> mainController(string filename){
	Vector_Matrix_Float image(28,vector<float>(28,0.0));
	image = imageFromText(filename);
	return softmax(FC_Final(FC_2(FC_1(Pool_2(Conv_2(Pool_1(Conv_1(image))))))));
}

void maxExpectations(vector<float> v){
	vector<float> a(5,0.0);
	vector<float> b(5,0.0);
	for(int h=0;h<5;h++){
		a[h] = v[0];
		for(int i =0;i<v.size();i++){
			if(v[i]>a[h]){
				a[h]=v[i];
				b[h]=i;
			}
		}
		v[(b[h])]=0;
	}
	cout<<"---------------------------------------------------------"<<endl;
	cout<<"Prediction on the numbers with highest 5 probabilities: ";
	for(int k=0;k<5;k++){
		cout<<endl<<b[k]<<": "<<a[k]*100<<" %";
	}
	cout<<endl<<"---------------------------------------------------------";
	cout<<endl;

}

int main()
{
	cout<<"\n";
	// string filename;
	// cout<<"Enter img filename: ";
	// cin>>filename;
	// cout<<endl;
	// maxExpectations(mainController(filename));
	maxExpectations(mainController("image.txt"));
	//print(mainController("image.txt"));
	
	//print(FC_2(FC_1(Pool_2(Conv_2(Pool_1(Conv_1(imageFromText("1_new.txt")))))))[1]);
	//Vector_Tetris_Float fuck = (((Conv_2(Pool_1(Conv_1(imageFromText("1_new.txt")))))));
	//print(((fuck))[2]); //testing result from Conv_1
	//cout<<FC_1(Pool_2(Conv_2(Pool_1(Conv_1(imageFromText("1_new.txt")))))).size();
	
	//print(mainController("2_new.txt"));
	//print(Conv_1(imageFromText("1_new.txt"))[0]);

	//print(imageFromText("1_new.txt"));//image matrix from txt
	//print(mainController("1_new.txt"));//final output
	
	//Checking takeFilter.h
	//filterBias("conv1.txt",)

	cout<<endl;	
	return 0;
}
