#include <bits/stdc++.h> 
#include <chrono>
using namespace std::chrono;
using namespace std; 
  
// maximum size of matrix 
#define MAX 4
  
// maximum number of threads 
#define MAX_THREAD 5
  
int matA[MAX][MAX]; 
int matB[MAX][MAX]; 
int matC[MAX][MAX]; 
int step_i = 0;

double timeExcecution = 0.0; 
void* multi(void* arg) 
{ 
    int core = step_i++; 
  
    // Each thread computes 1/4th of matrix multiplication 
    for (int i = core * MAX / 4; i < (core + 1) * MAX / 4; i++)  
        for (int j = 0; j < MAX; j++)  
            for (int k = 0; k < MAX; k++)  
                matC[i][j] += matA[i][k] * matB[k][j]; 
} 
  
void mult_regular(int matA[][MAX], int matB[][MAX]){
    //int matC[MAX][MAX];
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            for(int k=0;k<MAX;k++){
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }

    //Display matC
    cout << endl 
         << "Multiplication of A and B without using pthreads:" << endl;
    for(int h1=0;h1<MAX;h1++){
        for(int h2=0;h2<MAX;h2++){
            cout<<matC[h1][h2]<<" ";
        }
        cout<<endl;
    }
}

void mult_using_pthread(int matA[][MAX], int matB[][MAX]){
    pthread_t threads[MAX_THREAD]; 
  
    // Creating four threads, each evaluating its own part 
    for (int i = 0; i < MAX_THREAD; i++) { 
        int* p; 
        pthread_create(&threads[i], NULL, multi, (void*)(p)); 
    } 
  
    // joining and waiting for all threads to complete 
    for (int i = 0; i < MAX_THREAD; i++)  
        pthread_join(threads[i], NULL);     
  
    //Displaying the result matrix 
    cout << endl 
         << "Multiplication of A and B using pthreads" << endl; 
    for (int i = 0; i < MAX; i++) { 
        for (int j = 0; j < MAX; j++)  
            cout << matC[i][j] << " ";         
        cout << endl; 
    } 
}


auto time_pthread(int matA[][MAX], int matB[][MAX]){
    auto start1 = high_resolution_clock::now();
    mult_using_pthread(matA, matB);
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1-start1);
    return duration.count();
}




// Driver Code 
int main() 
{ 
    // Generating random values in matA and matB 
    for (int i = 0; i < MAX; i++) { 
        for (int j = 0; j < MAX; j++) { 
            matA[i][j] = i+1; 
            matB[i][j] = i+1; 
        } 
    } 
  
    // // Displaying matA 
    // cout << endl 
    //      << "Matrix A" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matA[i][j] << " "; 
    //     cout << endl; 
    // } 
  
    // // Displaying matB 
    // cout << endl 
    //      << "Matrix B" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matB[i][j] << " ";         
    //     cout << endl; 
    // } 
  
    // // Displaying the result matrix 
    // cout << endl 
    //      << "Multiplication of A and B" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matC[i][j] << " ";         
    //     cout << endl; 
    // } 
    auto start1 = high_resolution_clock::now();
    mult_using_pthread(matA, matB);
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1-start1);
    cout<<endl<<time_pthread(matA, matB)<<endl;

    cout<<"\n";
    // // Displaying matA 
    // cout << endl 
    //      << "Matrix A" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matA[i][j] << " "; 
    //     cout << endl; 
    // } 
  
    // // Displaying matB 
    // cout << endl 
    //      << "Matrix B" << endl; 
    // for (int i = 0; i < MAX; i++) { 
    //     for (int j = 0; j < MAX; j++)  
    //         cout << matB[i][j] << " ";         
    //     cout << endl; 
    // }
    // cout<<"\n\n";
    auto start2 = high_resolution_clock::now();
    mult_regular(matA, matB);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2-start2);
    cout<<endl<<duration2.count()<<endl;
    return 0; 
} 