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
__int128 generateLargePrime128(int bitLength);
bool isPrime(long long n);
long long modPow(long long base, long long exponent, long long mod);
long long gcd(long long a, long long b);
__int128 gcd(__int128 a, __int128 b);
long long binaryGCD(long long a, long long b);
long long exntendedGCD(long long a, long long b, long long &x, long long &y);
__int128 extendedGCD(__int128 a, __int128 b, __int128 &x, __int128 &y);
long long modInverse(long long a, long long b);
__int128 modInverse(__int128 a, __int128 m);

long long rsaEncrypt(long long m, long long e, long long n);
__int128 rsaEncrypt(__int128 m, __int128 e, __int128 n);
long long rsaDecrypt(long long c, long long d, long long n);
__int128 rsaDecrypt(__int128 c, __int128 d, __int128 n);