#include <iostream>
#include <fstream>
#include <iomanip>
#include "Encrypt.h"
using namespace std;

void div(string);
void totalTime(double);

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

    long long p = generateLargePrime(16);
    long long q = generateLargePrime(16);
    long long n = p * q;
    long long phi = (p-1) * (q-1);

    long long e = 65537;
    while (gcd(e, phi) != 1)
        e += 2;

    long long d = modInverse(e, phi);
    long long message = 12345;
    long long cipher = rsaEncrypt(message, e, n);
    long long decrypted = rsaDecrypt(cipher, d, n);

    cout << "(Large prime #1) p = " << p << endl;
    cout << "(Large prime #2) q = " << q << endl;
    cout << "(Modulus) n = " << n << endl;
    cout << "(Euler's Totient Function) phi = " << phi << endl;
    cout << "(Public Exponent) e = " << e << endl;
    cout << "(Private Exponent) d = " << d << endl;
    cout << "c = m^e % n" << endl;
    cout << "m = c^d % n" << endl;
    cout << "Original message: " << message << endl;
    cout << "Encrypted: " << cipher << endl;
    cout << "Decrypted: " << decrypted << endl;

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