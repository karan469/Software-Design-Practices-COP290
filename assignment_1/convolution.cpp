#include <iostream>
#include <algorithm>
#include <vector>
#define Vector_Matrix vector<vector<int>>
using namespace std;


// void print(vector<int> const &input){
//     // for(unsigned i=0;i<input.size();i++){
//     //     cout<<input.at(i)<<" ";
//     // }
//     for(auto it = input.cbegin();it!=input.cend();it++){
//         std::cout<<*it<<" ";
//     }
// }

void print(Vector_Matrix v){
    for(int i=0;i<v.size();i++){
      for(int j=0;j<v[0].size();j++){
          cout<<v[i][j]<<" ";
          
      }
      cout<<endl;
  }
}

int sub_convo(Vector_Matrix v1, Vector_Matrix v2){
    int sum = 0;
    int n = v1[0].size();
    for(int i = 0;i<n;i++){
        for(int j=0;j<n;j++){
            sum += v1[i][j]*v2[n-i-1][n-j-1];
        }
    }
    return sum;
}
// void sub_vector(vector<vector<int>> as, int n, int a, int b){
//     vector<vector<int>> sol;
//     for(int i=0;i<n;i++){
//         for(int j=0;j<n;j++){
//             sol[i][j] = as[i+a][j+b];
//         }
//     }
//     print(sol);
// }

Vector_Matrix convolution(Vector_Matrix v1, Vector_Matrix v2){
    // v1: kernel
    
    int rows_v1 = v1.size();
    int rows_v2 = v2.size();
    int coloumns_v1 = v1[0].size();
    int coloumns_v2 = v2[0].size();
    int n = rows_v1;
    
    Vector_Matrix v((rows_v2-rows_v1+1),vector<int>((coloumns_v2-coloumns_v1+1),0)); //answer here
    Vector_Matrix v_temp(n,vector<int>(n,0)); //Extraction of smaller matrix from image matrix
    
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
Vector_Matrix convolution_pad(Vector_Matrix v2, int padding){
    Vector_Matrix pad(v2.size()+2*padding,vector<int>(v2[0].size()+2*padding,0));
    for(int q=0;q<v2.size();q++){
        for(int w=0;w<v2[0].size();w++){
            pad[q+padding][w+padding] = v2[q][w];
        }
    }
    return pad;
}

// Vector_Matrix Convo_fast(Vector_Matrix v2, Vector_Matrix v1, string padding){
//     //Part1: Making Matrix toeplitz
//     //Part2: Matrix Multiplication

//     //v1: Kernel
//     int rows_v1 = v1.size();
//     int rows_v2 = v2.size();
//     int coloumns_v1 = v1[0].size();
//     int coloumns_v2 = v2[0].size();
//     int n = rows_v1;

//     Vector_Matrix v((rows_v2-rows_v1+1),vector<int>((coloumns_v2-coloumns_v1+1),0)); //answer here
//     Vector_Matrix v_temp(n,vector<int>(n,0)); //Extraction of smaller matrix from image matrix

//     //Part1//
//     //Adding padding
//     string addpad = "addpadding";
//     if(padding == addpad){
//         int pad;
//         pad = (rows_v1 - 1)/2;
//         v2 = convolution_pad(v2, pad);
//     }
//     // make toeplitz matrix
//     vector<int> lin_v1(rows_v1*coloumns_v1,0);
//     vector<int> lin_v2(rows_v2*coloumns_v2,0);
    
//     Vector_Matrix toepMat()
// }

int main(int argc, char const *argv[])
{
  //int kernel = {{1,2},{2,3},{3,4}};
  Vector_Matrix v2{{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6}};
  Vector_Matrix v1{{1,2,3},{1,2,3},{1,2,3}};
  //vector<vector<int>> v3{{3,4,5},{3,4,5},{3,4,5}};
  Vector_Matrix pad;
  pad = convolution_pad(v2,0);
    print(convolution(v1,pad));
  //cout<<sub_convo(v1,v2);
  return 0;
}
