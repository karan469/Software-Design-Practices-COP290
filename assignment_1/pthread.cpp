#include <bits/stdc++.h> 
#include <pthread.h>
#include <chrono>
using namespace std::chrono;
using namespace std; 
  
// maximum numb er of threads 
#define MAX_THREAD 4

// maximum size of matrix 
#define MAX 23100

struct maxisize{int maxi;};

struct maxisize t1 = {23100};

int matA[MAX][MAX]; 
int matB[MAX][1]; 
int matC[MAX][1]; 
int step_i = 0;

double timeExcecution = 0.0; 
void* multi(void* arg) 
{ 
    int core = step_i++; 
  
    // Each thread computes 1/4th of matrix multiplication 
    for (int i = core * t1.maxi / 4; i < (core + 1) * t1.maxi / 4; i++)  
            for (int k = 0; k < t1.maxi; k++)  
                matC[i][0] += matA[i][k] * matB[k][0]; 
}

void mult_using_pthread(int matA[][MAX], int matB[][1]){
    //int matC[m][k];
    pthread_t threads[MAX_THREAD]; 
  
    // Creating four threads, each evaluating its own part 
    for (int i = 0; i < MAX_THREAD; i++) { 
        int* p; 
        pthread_create(&threads[i], NULL, multi, (void*)(p)); 
    } 
  
    // joining and waiting for all threads to complete 
    for (int i = 0; i < MAX_THREAD; i++)  
        pthread_join(threads[i], NULL);     
  
    // Displaying the result matrix 
    cout << endl 
         << "Multiplication of A and B" << endl; 
    for (int i = 0; i < t1.maxi; i++) { 
        cout << matC[i][0] << " ";         
        cout << endl; 
    }

}


auto time_pthread(int matA[][MAX], int matB[][1]){
    auto start1 = high_resolution_clock::now();
    mult_using_pthread(matA, matB);
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1-start1);
    return duration.count();
}


// void controllerPthread(int matA[][MAX])

// Driver Code 
int main() 
{ 
    int n = 0;
    cin>>n;
    t1.maxi = n;
    for (int i = 0; i < t1.maxi; i++) { 
        for (int j = 0; j < t1.maxi; j++) { 
            matA[i][j] = rand()%225;  
        } 
    } 
    for(int h=0;h<t1.maxi;h++){
        
        matB[h][0] = rand()%3;
        
    }

    cout<<time_pthread(matA, matB);
    cout<<"\n";

    return 0; 
} 
