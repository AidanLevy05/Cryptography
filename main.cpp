#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Encrypt.h"
using namespace std;

void div(string);
void totalTime(double);
string toString(__int128 x);

int main() {

    div("Prime test");
    long long numbers[] = {
        32416190071,
        982451653,
        67280421310721,
        9999999967,
        32416187567,
        2305843009213693951,
        9223372036854775783,
        9223372036854775783LL
    };

    int count = sizeof(numbers) / sizeof(numbers[0]);

    startTimer();
    for (int i = 0; i < count; i++) {
        if (isPrime(numbers[i])) {
            cout << "Prime: " << numbers[i] << endl;
        } else {
            cout << "Composite: " << numbers[i] << endl;
        }
    }
    double time = stopTimer();
    totalTime(time);

    div("Prime generation test");

    vector<long long> primes;
    int numPrimes = 3;
    startTimer();
    for (int i = 0; i < numPrimes; i++)
        primes.push_back(generateLargePrime(32));
    time = stopTimer();
    totalTime(time);

    for (auto v : primes) {
        cout << v << " | ";

        if (isPrime(v))
            cout << "Prime" << endl;
        else 
            cout << "Composite" << endl;
    }

    div("GCF Test");

    int n1 = 40;
    int n2 = 48;
    int gcf = binaryGCD(n1, n2);

    startTimer();
    cout << "The GCF of " << n1 << " and " << n2 << " is: " << gcf << endl;
    time = stopTimer();
    totalTime(time);

    div("rsaEncrypt and rsaDecrypt test");

    int primeBitSize = 1;
    cout << "Enter prime bit size: " << endl;
    cin >> primeBitSize;

    __int128 p, q;
    if (primeBitSize >= 32) {
        p = generateLargePrime128(primeBitSize);
        q = generateLargePrime128(primeBitSize);
    } else {
        p = generateLargePrime(primeBitSize);
        q = generateLargePrime(primeBitSize);
    }
    
    if (p == q) {
        throw string("Error: p and q are equal.");
    }
    __int128 n = p * q;
    __int128 phi = (p-1) * (q-1);

    __int128 e = 65537;
    if (gcd(e, phi) != 1) {
        cout << "65537 not coprime. Trying fallback small e" << endl;
        e = 17;
        while (gcd(e, phi) != 1) 
            e += 2;
    }

    __int128 d = modInverse(e, phi);
    if ((__int128(e)*d)%phi != 1) {
        throw string("Error: e*d % phi != 1. Modular inverse broken.");
    }
    __int128 message = 12345;
    if (message >= n) {
        throw string("Error: Message too large. Must be less than modulus n.");
    }
    __int128 cipher = rsaEncrypt(message, e, n);
    __int128 decrypted = rsaDecrypt(cipher, d, n);

    cout << "(Large prime #1) p = " << toString(p) << endl;
    cout << "(Large prime #2) q = " << toString(q) << endl;
    cout << "(Modulus) n = " << toString(n) << endl;
    cout << "(Euler's Totient Function) phi = " << toString(phi) << endl;
    cout << "(Public Exponent) e = " << toString(e) << endl;
    cout << "(Private Exponent) d = " << toString(d) << endl;
    cout << "c = m^e % n" << endl;
    cout << "m = c^d % n" << endl;
    cout << "Original message: " << toString(message) << endl;
    cout << "Encrypted: " << toString(cipher) << endl;
    cout << "Decrypted: " << toString(decrypted) << endl;

    return 0;
    
}

void div(string m) {
    cout << endl;
    if (m != "") 
        cout << m << " ";
    for (int i = 0; i < 25; i++)
        cout << "-";
    cout << endl << endl;
}

void totalTime(double t) {
    cout << fixed << setprecision(10);
    cout << "Total time: " << t << " seconds" << endl;
}

string toString(__int128 x) {
    if (x == 0) return "0";

    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }

    string s;
    while (x > 0) {
        s += '0' + (x % 10);
        x /= 10;
    }

    if (neg)
        s += '-';
    
    reverse(s.begin(), s.end());
    return s;
}