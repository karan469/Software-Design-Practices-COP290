#include <iostream>
#include <algorithm>
#include <vector>	
#include <thread>
#include <ctime>
#include <random>
#include <chrono>
#include <cmath>
#include "vehicle.h"
using namespace std;


int main(int argc, char const *argv[])
{
    vehicle car = vehicle();
    vehicle *c;
    c = &car;

    car.x1 = 5; c->x1 = 6;
    cout << car.x1<<endl;

    float n = 1.5;
    int p = (int)round(n);
    cout << p << endl;
    return 0;
}
