/*

Author: Aidan Levy
Creation Date: May 24, 2025

*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;



/*
Name: isPrime()
Parameters: long long
Return: bool
Description: 

Returns true if the number if prime; false if composite. 
*/
bool isPrime(long long n);

/*
Name: modPow
Parameters: long long base, long long exponent, long long mod
Return: long long
Description: 

Performed modular exponentiation (base ^ exponent) % mod efficiently.
*/
long long modPow(long long base, long long exponent, long long mod);