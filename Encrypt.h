/*

Author: Aidan Levy
Creation Date: May 24, 2025

*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <random>
#include <omp.h>
using namespace std;
using namespace std::chrono;

extern std::chrono::high_resolution_clock::time_point global_start;

void startTimer();
double stopTimer();

long long generateLargePrime(int bitLength);
bool isPrime(long long n);
long long modPow(long long base, long long exponent, long long mod);
long long gcd(long long a, long long b);
long long binaryGCD(long long a, long long b);
long long extendedGCD(long long a, long long b, long long &x, long long &y);
long long modInverse(long long a, long long m);

long long rsaEncrypt(long long m, long long e, long long n);
long long rsaDecrypt(long long c, long long d, long long n);