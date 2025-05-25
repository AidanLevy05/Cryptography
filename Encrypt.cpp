/*

Author: Aidan Levy
Creation Date: May 24, 2025

*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*
Name: 
Parameters: 
Return: 
Description: 
*/

/*
Name: isPrime()
Parameters: long long
Return: bool
Description: 

Returns true if the number if prime; false if composite. 
*/
bool isPrime(long long n) {
    if (n <= 1) {
        return false;
    }

    // Step 1: Factor out the largest power of 2 from n-1.
    long long k = n-1;
    int e = 0;

    while (k % 2 == 0) {
        k /= 2;
        e++;
    }

    // Now, we know that n = (k * 2^e) + 1 if e >= 1 && k % 2 != 0
    int bases[] = {2, 3, 5, 7, 11};
    for (int i = 0; i < 5; i++) {
        long long a = bases[i];

        if (a >= n-1)
            continue;

        long long x = modPow(a, k, n);
        if (x == 1 || x == n-1)
            continue;

        bool composite = true;
        for (long long r = 1; r < e; r++) {
            x = modPow(x, 2, n);
            if (x == n-1) {
                composite = false;
                break;
            }
        }

        if (composite)
            return false;
    }

    return true;
}

/*
Name: modPow
Parameters: long long base, long long exponent, long long mod
Return: long long
Description: 

Performed modular exponentiation (base ^ exponent) % mod efficiently.
*/
long long modPow(long long base, long long exponent, long long mod) {
    long long result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}