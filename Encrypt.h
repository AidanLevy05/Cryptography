/*

Author: Aidan Levy
Creation Date: May 24, 2025

*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;

extern std::chrono::high_resolution_clock::time_point global_start;

void startTimer();
double stopTimer();

bool isPrime(long long n);
long long modPow(long long base, long long exponent, long long mod);