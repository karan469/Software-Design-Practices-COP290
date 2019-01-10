// Example program
#include <iostream>
#include <algorithm>
#include <vector>
#define HIGH_VECTOR_INT vector<vector<int>>;
using namespace std;


// void print(vector<int> const &input){
//     // for(unsigned i=0;i<input.size();i++){
//     //     cout<<input.at(i)<<" ";
//     // }
//     for(auto it = input.cbegin();it!=input.cend();it++){
//         std::cout<<*it<<" ";
//     }
// }

void print(vector<vector<int>> v){
    for(int i=0;i<v.size();i++){
      for(int j=0;j<v[0].size();j++){
          cout<<v[i][j]<<" ";
          
      }
      cout<<endl;
  }
}

int sub_convo(vector<vector<int>> v1, vector<vector<int>> v2){
    int sum = 0;
    int n = v1[0].size();
    for(int i = 0;i<n;i++){
        for(int j=0;j<n;j++){
            sum += v1[i][j]*v2[n-i-1][n-j-1];
        }
    }
    return sum;
}
void sub_vector(vector<vector<int>> as, int n, int a, int b){
    vector<vector<int>> sol;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            sol[i][j] = as[i+a][j+b];
        }
    }
    print(sol);
}
void convulution(vector<vector<int>> v1, vector<vector<int>> v2){
    // v1: kernel
    vector<vector<int>> v;
    int rows_v1 = v1.size();
    int rows_v2 = v2.size();
    int coloumns_v1 = v1[0].size();
    int coloumns_v2 = v2[0].size();
    
    vector<vector<int>> v_temp;
    
    for(int x=0;x<(coloumns_v2-coloumns_v1+1);x++){
        for(int y=0;y<(rows_v2-rows_v1+1);y++){
            // v_temp = v2[x][y];
            for(int a=0;a<coloumns_v1;a++){
                for(int b=0;b<rows_v1;b++){
                    v_temp[a][b] = v2[a+x][b+y];
                }
            }
            v[x][y] = sub_convo(v1,v_temp);
            // cout<<v[x][y];
        }
    }
    print(v);
        
}

int main()
{
  //int kernel = {{1,2},{2,3},{3,4}};
  vector<vector<int>> v2{{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6},{1,2,3,4,5,6}};
  vector<vector<int>> v1{{1,2,3},{1,2,3},{1,2,3}};
  //vector<vector<int>> v3{{3,4,5},{3,4,5},{3,4,5}};
  //vector<vector<int>> v2 = convulution(v1,v);
  sub_vector(v2,3,0,2);
  //cout<<sub_convo(v1,v2);
    
  return 0;
}