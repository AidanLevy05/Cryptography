/*

Author: Aidan Levy
Creation Date: May 24, 2025

*/

#include "Encrypt.h"

std::chrono::high_resolution_clock::time_point global_start;

/*
Name: 
Parameters: 
Return: 
Description: 
*/

/*
Name: startTimer()
Parameters: N/A
Return: void
Description: 

Stores time in a global variabke
*/
void startTimer() {
    global_start = high_resolution_clock::now();
}

/*
Name: stopTimer()
Parameters: N/A
Return: chrono::duration<double>
Description: 

Returns elapsed time since startTimer() was called
*/
double stopTimer() {
    high_resolution_clock::time_point global_end = high_resolution_clock::now();
    return duration_cast<duration<double>>(global_end - global_start).count();
}

/*
Name: generateLargePrime()
Parameters: int bitLength
Return: long long
Description: 

Generates a random prime number of approximately 'bitLength' bits
using the isPrime() function to validate
*/
long long generateLargePrime(int bitLength) {
    long long result = 0;
    bool found = false; 

    #pragma omp parallel
    {
        mt19937_64 gen(random_device{}());
        long long min = (1LL << (bitLength - 1));
        long long max = (1LL << bitLength) - 1;
        uniform_int_distribution<long long> dist(min, max);

        while (!found) {
            long long candidate = dist(gen);
            if (candidate % 2 == 0)
                candidate++;

            if (isPrime(candidate)) {
                #pragma omp critical
                {
                    if (!found) {
                        found = true;
                        result = candidate;
                    }
                }
            }
        }
    }
    return result;
}

/*
Name: generateLargePrime128()
Parameters: int bitLength
Return: long long
Description: 

Generates a random prime number of approximately 'bitLength' bits
using the isPrime() function to validate
*/
__int128 generateLargePrime128(int bitLength) {
    __int128 result = 0;
    bool found = false;

    #pragma omp parallel
    {
        mt19937_64 gen(random_device{}());

        while (!found) {
            __int128 candidate = 0;

            candidate = (__int128)gen() << 64 | gen();

            int extraBits = 128 - bitLength;
            candidate = candidate >> extraBits;
            candidate |= (__int128)1 << (bitLength - 1);

            if (candidate % 2 == 0)
                candidate++;

            if (isPrime(candidate)) {
                #pragma omp critical
                {
                    if (!found) {
                        found = true;
                        result = candidate;
                    }
                }
            }
        }
    }

    return result;
}


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
    int size = 12;
    int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < size; i++) {
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
Name: modPow()
Parameters: long long base, long long exponent, long long mod
Return: long long
Description: 

Performed modular exponentiation (base ^ exponent) % mod efficiently.
*/
long long modPow(long long base, long long exponent, long long mod) {
    __int128 result = 1;
    __int128 b = base % mod;

    while (exponent > 0) {
        if (exponent & 1) 
            result = (result * b) % mod;
        b = (b * b) % mod;
        exponent >>= 1;
    }

    return (long long)result;
}

/*
Name: gcd()
Parameters: long long a, long long b
Return: long long 
Description: 

Returns greatest common denominator between two numbers
*/
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/*
Name: gcd()
Parameters: __int128 a, __int128 b
Return: __int128 
Description: 

Returns greatest common denominator between two numbers
*/
__int128 gcd(__int128 a, __int128 b) {
    while (b != 0) {
        __int128 temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/*
Name: binaryGCD()
Parameters: long long a, long long b
Return: long long
Description: 

Uses subtraction, bit shifting and comparisons to return
the greatest common denominator between two numbers
using Stein's algorithm
*/
long long binaryGCD(long long a, long long b) {
    if (a == 0) return b;
    if (b == 0) return a;

    // shift stores how many times a or b is divisible by 2.
    int shift = __builtin_ctzll(a | b);

    // Divide a by 2^(shift), making it odd
    a >>= __builtin_ctzll(a);

    while (b != 0) {
        // make b odd by removing all factors of 2
        b >>= __builtin_ctzll(b);
        // a is always the smaller number
        if (a > b)
            swap(a,b);
        // since both a and b are odd, b-a is even
        b -= a;
    }
    return a << shift;
}

/*
Name: extendedGCD()
Parameters: long long a, long long b, long long &x, long long &y
Return: long long
Description: 

Uses the extended Euclidean algorithm to find x and y such that
a*x + b*y = gcd(a, b).
Returns gcd(a, b).
*/
long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = extendedGCD(b, a%b, x1, y1);

    x = y1;
    y = x1 - (a/b) * y1;

    return gcd;
}

/*
Name: extendedGCD()
Parameters: __int128 a, __int128 b, __int128 &x, __int128 &y
Return: __int128
Description: 

Uses the extended Euclidean algorithm to find x and y such that
a*x + b*y = gcd(a, b).
Returns gcd(a, b).
*/
__int128 extendedGCD(__int128 a, __int128 b, __int128 &x, __int128 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    __int128 x1, y1;
    __int128 gcd = extendedGCD(b, a%b, x1, y1);

    x = y1;
    y = x1 - (a/b) * y1;

    return gcd;
}

/*
Name: modInverse()
Parameters: long long a, long long m
Return: long long
Description: 

Returns the modular inverse of a modulo m using the
extended Euclidean algorithm. If no inverse exists,
return throw error.
*/
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = extendedGCD(a, m, x, y);

    if (g != 1)
        throw string("Error: No modular inverse found.");

    return (x % m + m) % m;
}

/*
Name: modInverse()
Parameters: __int128 a, __int128 m
Return: __int128
Description: 

Returns the modular inverse of a modulo m using the
extended Euclidean algorithm. If no inverse exists,
return throw error.
*/
__int128 modInverse(__int128 a, __int128 m) {
    __int128 x, y;
    __int128 g = extendedGCD(a, m, x, y);

    if (g != 1)
        throw string("Error: No modular inverse found.");

    __int128 result = (x % m + m) % m;
    if ((a * result) % m != 1) {
        throw string("Error: modInverse verification failed");
    }

    return result;
}

/*
Name: rsaEncrypt()
Parameters: long long m, long long e, long long n
Return: long long
Description: 

Encrypts a message m using the RSA public key (e, n). 
Returns the ciphertext c = m^e % n.
*/
long long rsaEncrypt(long long m, long long e, long long n) {
    return modPow(m, e, n);
}

/*
Name: rsaEncrypt()
Parameters: __int128 m, __int128 e, __int128 n
Return: __int128
Description: 

Encrypts a message m using the RSA public key (e, n). 
Returns the ciphertext c = m^e % n.
*/
__int128 rsaEncrypt(__int128 m, __int128 e, __int128 n) {
    return modPow(m, e, n);
}

/*
Name: rsaDecrypt()
Parameters: long long c, long long d, long long n
Return: long long
Description: 

Decrypts a ciphertext c using the RSA private key (d, n). 
Returns the original message m = c^d % n.
*/
long long rsaDecrypt(long long c, long long d, long long n) {
    return modPow(c, d, n);
}

/*
Name: rsaDecrypt()
Parameters: __int128 c, __int128 d, __int128 n
Return: __int128
Description: 

Decrypts a ciphertext c using the RSA private key (d, n). 
Returns the original message m = c^d % n.
*/
__int128 rsaDecrypt(__int128 c, __int128 d, __int128 n) {
    return modPow(c, d, n);
}